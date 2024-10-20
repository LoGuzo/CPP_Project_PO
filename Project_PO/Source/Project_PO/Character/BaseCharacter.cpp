// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../AnimInstance/BaseAnimInstance.h"
#include "../Component/StatComponent/StatComponent.h"
#include "../Component/SkillComponent/SkillComponent.h"
#include "../Manager/BaseGameInstance.h"

ABaseCharacter::ABaseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;

	SkillComponent = CreateDefaultSubobject<USkillComponent>("SkillComponent");
}

void ABaseCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (SkillComponent && StatComponent)
		SkillComponent->SetStatComponent(StatComponent);
}

void ABaseCharacter::ControlSkill(int32 const& SkillID)
{
	if (SkillComponent)
		SkillComponent->UseSkill(SkillID);

	bIsAttack = true;
}

void ABaseCharacter::PlaySkill(FString const& SkillName, float const& AttackSpeed)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		int32 SkillID = *SkillMontageMap.Find(SkillName);
		TSharedPtr<FBaseSkillData> Data = GameInstance->GetDatabaseMap<FBaseSkillData>(E_ManagerType::E_SkillDatabaseManager, SkillID);
		if (Data.IsValid())
		{
			UBaseAnimInstance* AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
			if (AnimInstance)
				AnimInstance->PlaySome(Data.Get(), AttackSpeed);
		}
	}
}

void ABaseCharacter::AddSkillMap(TArray<int32> SkillIDs)
{
	for (int32 const& SkillID : SkillIDs)
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			TWeakPtr<FBaseSkillData> Data = GameInstance->GetDatabaseMap<FBaseSkillData>(E_ManagerType::E_SkillDatabaseManager, SkillID);
			if (Data.IsValid())
			{
				FString str = Data.Pin()->SkillName.ToString();
				SkillMontageMap.Emplace(Data.Pin()->SkillName.ToString(), SkillID);
			}
		}
	}

	if (SkillComponent)
		SkillComponent->SetUpSkillMap(SkillIDs);
}

void ABaseCharacter::Died()
{
	bIsDied = true;
}

void ABaseCharacter::DiedNotify()
{
	SetState(false);
}

void ABaseCharacter::SetState(bool NowState)
{
	bIsDied = !NowState;

	SetActorHiddenInGame(!NowState);
	SetActorEnableCollision(NowState);
	SetActorTickEnabled(NowState);

	if (NowState)
	{
		GetCharacterMovement()->GravityScale = 1.f;
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	else
	{
		if (StatComponent)
			StatComponent->ResetStat();

		GetCharacterMovement()->GravityScale = 0.f;
		GetCharacterMovement()->DisableMovement();
	}

}


