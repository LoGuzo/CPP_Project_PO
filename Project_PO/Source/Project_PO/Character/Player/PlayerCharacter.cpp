// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h" 
#include "InputMappingContext.h" 
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../Actor/Item/Equip/Weapon/BaseWeaponActor.h"
#include "../../AnimInstance/BasePlayerAnimInstance.h"
#include "../../Component/InteractionComponent.h"
#include "../../Component/EquipComponent.h"
#include "../../Component/InventoryComponent.h"
#include "../../Component/StatComponent/PlayerStatComponent.h"
#include "../../Component/QuickSlotComponent/PotionQuickSlotComponent.h"
#include "../../Interface/Interactable.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/WidgetManager.h"
#include "../../Widget/Etc/CrosshairEtcWidget.h"
#include "../../Widget/InGame/Inventory/MainInventoryWidget.h"

APlayerCharacter::APlayerCharacter()
	: bIsAiming(false)
	, bIsArmed(false)
	, InteractActor(nullptr)
{
	BindInputAction();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	CameraTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CameraTimeline"));

	// Setup Component
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("Interaction");
	EquipComponent = CreateDefaultSubobject<UEquipComponent>("EquipComponent");
	StatComponent = CreateDefaultSubobject<UPlayerStatComponent>(TEXT("StatComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	PotionQuickSlotComponent = CreateDefaultSubobject<UPotionQuickSlotComponent>(TEXT("PotionQuickSlot"));

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 70.f);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	SetupCurve();

	Tags.Add(TEXT("Player"));
}

void APlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	SetupCameraCurve();
	SetupCamera();
	SetupStatComponent();
	SetupInventoryComponent();
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDied)
		return 0.f;

	if (StatComponent)
		StatComponent->TakeDamage(DamageAmount);

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CameraTimeline)
		CameraTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
}

void APlayerCharacter::Jump()
{
	Super::Jump();
	bIsSprint = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);

		//Aiming
		EnhancedInputComponent->BindAction(AimingAction, ETriggerEvent::Triggered, this, &APlayerCharacter::TriggeredAiming);
		EnhancedInputComponent->BindAction(AimingAction, ETriggerEvent::Canceled, this, &APlayerCharacter::CanceledAiming);
		EnhancedInputComponent->BindAction(AimingAction, ETriggerEvent::Completed, this, &APlayerCharacter::CompletedAiming);

		//Sprint
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APlayerCharacter::TriggeredSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Canceled, this, &APlayerCharacter::CanceledSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::CompletedSprint);

		//Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);

		//Skill
		EnhancedInputComponent->BindAction(UseSkillAction, ETriggerEvent::Triggered, this, &APlayerCharacter::UseSkill);

		//Inven
		EnhancedInputComponent->BindAction(InvenAction, ETriggerEvent::Started, this, &APlayerCharacter::ShowInven);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (MovementVector.Y == 1.f)
	{
		bIsMoveFront = true;
	}
	else
	{
		bIsSprint = false;
		bIsMoveFront = false;
	}

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Interact(const FInputActionValue& Value)
{
	if (InteractActor)
	{
		IInteractable* interactActor = Cast<IInteractable>(InteractActor);
		if (interactActor)
			interactActor->Interact(this);
	}
	else
	{
		if (InteractionComponent)
		{
			InteractionComponent->InstallObject(FVector(), FRotator());
		}
	}
}

void APlayerCharacter::TriggeredAiming(const FInputActionValue& Value)
{
	if (bIsArmed)
	{
		if (bIsSprint)
			return;
		if (!bIsAiming)
		{
			bIsAiming = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;

			if (CameraTimeline)
				CameraTimeline->Play();
			DisplayCrosshair();
		}
	}
}

void APlayerCharacter::CanceledAiming(const FInputActionValue& Value)
{
	if (bIsAiming)
	{
		bIsAiming = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;

		if (CameraTimeline)
			CameraTimeline->Reverse();
		DisplayCrosshair();
	}
}

void APlayerCharacter::CompletedAiming(const FInputActionValue& Value)
{
	if (bIsAiming)
	{
		bIsAiming = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;

		if (CameraTimeline)
			CameraTimeline->Reverse();
		DisplayCrosshair();
	}
}

void APlayerCharacter::TriggeredSprint(const FInputActionValue& Value)
{
	if (StatComponent)
	{
		UPlayerStatComponent* PlayerComponent = GetStatComponent<UPlayerStatComponent>();
		if (PlayerComponent)
		{
			if (GetCharacterMovement()->IsFalling() || !bIsMoveFront)
			{
				GetCharacterMovement()->MaxWalkSpeed = PlayerComponent->GetSpeed();
				bIsSprint = false;
				return;
			}

			bIsSprint = true;
			GetCharacterMovement()->MaxWalkSpeed = PlayerComponent->GetSpeed() + 200.f;
			if (bIsAiming)
			{
				bIsAiming = false;
				if (CameraTimeline)
					CameraTimeline->Reverse();
				DisplayCrosshair();
			}
		}
	}
}

void APlayerCharacter::CanceledSprint(const FInputActionValue& Value)
{
	if (StatComponent)
	{
		GetCharacterMovement()->MaxWalkSpeed = GetStatComponent<UPlayerStatComponent>()->GetSpeed();
		bIsSprint = false;
	}
}

void APlayerCharacter::CompletedSprint(const FInputActionValue& Value)
{
	if (StatComponent)
	{
		GetCharacterMovement()->MaxWalkSpeed = GetStatComponent<UPlayerStatComponent>()->GetSpeed();
		bIsSprint = false;
	}
}

void APlayerCharacter::Attack(const FInputActionValue& Value)
{
	if (!bIsAiming || bIsAttack)
		return;

	bIsAttack = true;

	AttackMontage();
}

void APlayerCharacter::UseSkill(const FInputActionValue& Value)
{
}

void APlayerCharacter::ShowInven(const FInputActionValue& Value)
{
	auto GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UBaseUserWidget* InvenWidget = WidgetManager->GetWidget<UMainInventoryWidget>(TEXT("Inven"));
			if (InvenWidget)
				InvenWidget->SetAddRemove();
		}
	}
}

void APlayerCharacter::BindInputAction()
{
	// Input Asset Load
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(TEXT("/Game/ThirdPerson/Input/IMC_Default.IMC_Default"));
	if (MappingContextFinder.Succeeded())
		DefaultMappingContext = MappingContextFinder.Object;

	// Jump Action Asset Load
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionObject(TEXT("/Game/ThirdPerson/Input/Actions/IA_Jump.IA_Jump"));
	if (JumpActionObject.Succeeded())
		JumpAction = JumpActionObject.Object;

	// Move Action Asset Load
	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionObject(TEXT("/Game/ThirdPerson/Input/Actions/IA_Move.IA_Move"));
	if (MoveActionObject.Succeeded())
		MoveAction = MoveActionObject.Object;

	// Camera Rotation and Action Asset Load
	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionObject(TEXT("/Game/ThirdPerson/Input/Actions/IA_Look.IA_Look"));
	if (LookActionObject.Succeeded())
		LookAction = LookActionObject.Object;

	// Interact Action Asset Load
	static ConstructorHelpers::FObjectFinder<UInputAction> InteractActionObject(TEXT("/Game/ThirdPerson/Input/Actions/IA_Interact.IA_Interact"));
	if (InteractActionObject.Succeeded())
		InteractAction = InteractActionObject.Object;

	// Aiming Action Asset Load
	static ConstructorHelpers::FObjectFinder<UInputAction> AimingActionObject(TEXT("/Game/ThirdPerson/Input/Actions/IA_Aiming.IA_Aiming"));
	if (AimingActionObject.Succeeded())
		AimingAction = AimingActionObject.Object;

	// Sprint Action Asset Load
	static ConstructorHelpers::FObjectFinder<UInputAction> SprintActionObject(TEXT("/Game/ThirdPerson/Input/Actions/IA_Sprint.IA_Sprint"));
	if (SprintActionObject.Succeeded())
		SprintAction = SprintActionObject.Object;

	// Attack Action Asset Load
	static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionObject(TEXT("/Game/ThirdPerson/Input/Actions/IA_Attack.IA_Attack"));
	if (AttackActionObject.Succeeded())
		AttackAction = AttackActionObject.Object;

	// UseSkill Action Asset Load
	static ConstructorHelpers::FObjectFinder<UInputAction> SkillActionObject(TEXT("/Game/ThirdPerson/Input/Actions/IA_UserSkill.IA_UserSkill"));
	if (SkillActionObject.Succeeded())
		UseSkillAction = SkillActionObject.Object;

	// Inven Action Asset Load
	static ConstructorHelpers::FObjectFinder<UInputAction> InvenActionObject(TEXT("/Game/ThirdPerson/Input/Actions/IA_Inven.IA_Inven"));
	if (SkillActionObject.Succeeded())
		InvenAction = InvenActionObject.Object;
}

void APlayerCharacter::SetupCurve()
{
	const ConstructorHelpers::FObjectFinder<UCurveFloat> CurveFloat(TEXT("/Game/TimeCurve/CameraCurve.CameraCurve"));
	if (CurveFloat.Succeeded())
		CameraCurve = CurveFloat.Object;
}

void APlayerCharacter::SetupCameraCurve()
{
	if (CameraCurve)
	{
		InterpFunction.BindUFunction(this, FName("Zoom"));
		if (CameraTimeline)
		{
			CameraTimeline->AddInterpFloat(CameraCurve, InterpFunction);
			CameraTimeline->SetLooping(false);
		}
	}
}

void APlayerCharacter::Zoom(float Value)
{
	FVector ZoomLocation = FMath::Lerp(InitailZoomLocation, TargetZoomLocation, Value);
	CameraBoom->SocketOffset = ZoomLocation;

	float ArmLength = FMath::Lerp(InitalSpringLength, TargetSpringLength, Value);
	CameraBoom->TargetArmLength = ArmLength;
}

void APlayerCharacter::SetupCamera()
{
	InitailZoomLocation = GetCameraBoom()->SocketOffset;
	InitalSpringLength = GetCameraBoom()->TargetArmLength;

	TargetZoomLocation = FVector(InitailZoomLocation.X, InitailZoomLocation.Y * 2, InitailZoomLocation.Z);
	TargetSpringLength = InitalSpringLength / 2;
}

void APlayerCharacter::SetupStatComponent()
{
	if (StatComponent)
		GetStatComponent<UPlayerStatComponent>()->SetStat(ID);
}

void APlayerCharacter::SetupInventoryComponent()
{
	if (InventoryComponent && PotionQuickSlotComponent)
	{
		InventoryComponent->SetQuickSlotComponent(PotionQuickSlotComponent);
	}
}

void APlayerCharacter::DisplayCrosshair()
{
	auto GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UBaseUserWidget* CrossWidget = WidgetManager->GetWidget<UCrosshairEtcWidget>(TEXT("CrosshairWidget"));
			if (CrossWidget)
				CrossWidget->SetShowHidden();
		}
	}
}

void APlayerCharacter::AttackMontage()
{
	ABaseWeaponActor* CurrentWeapon = EquipComponent->GetCurrentWeapon();
	if (CurrentWeapon)
	{
		AnimInstance = Cast<UBasePlayerAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			FString AttackString = *AttackMontageMap.Find(WeaponType);
			if (StatComponent)
			{
				float AttackSpeed = GetStatComponent<UPlayerStatComponent>()->GetAttackSpeed();
				PlaySkill(AttackString, AttackSpeed);
			}
		}
	}
}

FTransform APlayerCharacter::GetLeftHandSocketTransform()
{
	FTransform OutPutTransform;
	ABaseWeaponActor* Weapon = EquipComponent->GetCurrentWeapon();
	if (Weapon)
	{
		FVector OutputLocation = OutPutTransform.GetLocation();
		FRotator OutputRotation = OutPutTransform.GetRotation().Rotator();

		FTransform WeaponTransform = Weapon->GetSkeletalMesh()->GetSocketTransform(TEXT("LeftHandIK"));
		GetMesh()->TransformFromBoneSpace(TEXT("hand_r")
			, WeaponTransform.GetLocation(), WeaponTransform.GetRotation().Rotator()
			, OutputLocation, OutputRotation
		);

		OutPutTransform.SetLocation(OutputLocation);
		OutPutTransform.SetRotation(FQuat(OutputRotation));
	}
	return OutPutTransform;
}

void APlayerCharacter::ShotAttackCheck()
{
	ABaseWeaponActor* Weapon = EquipComponent->GetCurrentWeapon();
	if (Weapon)
		Weapon->Fire();
}

void APlayerCharacter::SetEquip(int32 ItemID)
{
	if (EquipComponent)
	{
		EquipComponent->SetEquipment(ItemID);
		SetIsArmed(true);
	}
}

void APlayerCharacter::AttackCheck()
{
	ABaseWeaponActor* Weapon = EquipComponent->GetCurrentWeapon();
	if (Weapon)
		Weapon->Fire();
}
