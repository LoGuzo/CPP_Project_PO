// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Character/BaseCharacter.h"
#include "../Manager/BaseGameInstance.h"

UBaseAnimInstance::UBaseAnimInstance()
	: bIsFalling(false)
	, ShouldMove(false)
	, GroundSpeed(0.f)
	, OwnerVelocity(FVector::ZeroVector)
	, OwnCharacter(nullptr)
{
}

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (GetOwningActor())
	{
		OwnCharacter = Cast<ABaseCharacter>(GetOwningActor());
		if (OwnCharacter)
			MovementComponent = OwnCharacter->GetCharacterMovement();
	}
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnCharacter)
	{
		OwnerVelocity = OwnCharacter->GetVelocity();
		
		if (MovementComponent)
		{
			bIsFalling = MovementComponent->IsFalling();

			if (bIsFalling)
				GroundSpeed = 0.f;
			else
				GroundSpeed = OwnerVelocity.Size();

			ShouldMove = GroundSpeed > 3.f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector;
		}
	}
}

TSoftObjectPtr<UAnimMontage> UBaseAnimInstance::FindMontage(int32 const& MontageID)
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

void UBaseAnimInstance::ColliderNotify()
{
	if (!OwnCharacter)
		return;

	switch (NowData->SkillType)
	{
	case E_SkillType::E_Melee:
		OwnCharacter->MeleeAttackCheck(NowData->Range, NowData->Coefficient);
		break;
	case E_SkillType::E_Scope:
		OwnCharacter->ScopeAttackCheck(NowData->Range, NowData->Coefficient);
		break;
	case E_SkillType::E_Shot:
		OwnCharacter->ShotAttackCheck();
		break;
	default:
		break;
	}
}

void UBaseAnimInstance::PlayMontage(TSoftObjectPtr<UAnimMontage> Montage, float AttackSpeed)
{
	UAnimMontage* AnimMontage = Montage.LoadSynchronous();
	if (AnimMontage)
	{
		if (!Montage_IsPlaying(AnimMontage))
			Montage_Play(AnimMontage, 1.f * AttackSpeed);
	}
}

void UBaseAnimInstance::PlaySome(FBaseSkillData* Data, float AttackSpeed)
{
	if (!Data)
		return;

	NowData = Data;

	UAnimMontage* AnimMontage = FindMontage(NowData->MontageID).LoadSynchronous();
	if (AnimMontage)
	{
		if (!Montage_IsPlaying(AnimMontage))
			Montage_Play(AnimMontage, 1.f * AttackSpeed);
	}
}

void UBaseAnimInstance::AnimNotify_Collider()
{
	ColliderNotify();
}

void UBaseAnimInstance::AnimNotify_AttackEnd()
{
	if (OwnCharacter)
		OwnCharacter->SetIsAttack(false);
}
