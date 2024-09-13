// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h" 
#include "InputMappingContext.h" 
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../Interface/Interactable.h"

APlayerCharacter::APlayerCharacter()
	: InteractActor(nullptr)
{
	BindInputAction();

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
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
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
	}

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

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
}
