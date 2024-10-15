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
#include "../Manager/BaseGameInstance.h"

ABaseCharacter::ABaseCharacter()
	: AttackIndex(0)
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
}

void ABaseCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ABaseCharacter::AnimMontage(FString const& MontageName)
{
	UBaseAnimInstance* AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		int32 MontageID = *AnimMontageMap.Find(MontageName);
		TSoftObjectPtr<UAnimMontage> Montage = FindMontage(MontageID);
		AnimInstance->PlayMontage(Montage, 1.f);
	}
}

TSoftObjectPtr<UAnimMontage> ABaseCharacter::FindMontage(int32 const& MontageID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FMontageData> Data = GameInstance->GetDatabaseMap<FMontageData>(E_ManagerType::E_MontageDatabaseManager, MontageID);
		if (Data.IsValid())
		{
			FMontageData MontageData = *Data.Pin();
			return MontageData.Montage;
		}
	}
	return TSoftObjectPtr<UAnimMontage>();
}

void ABaseCharacter::SetState(bool NowState)
{
	SetActorHiddenInGame(!NowState);
	SetActorEnableCollision(NowState);
	SetActorTickEnabled(NowState);
}


