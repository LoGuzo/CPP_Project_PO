// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerAnimInstance.h"
#include "../Character/Player/PlayerCharacter.h"

UBasePlayerAnimInstance::UBasePlayerAnimInstance()
	: bIsArmed(false)
	, bIsAiming(false)
	, Pitch(0.f)
	, WeaponType(E_WeaponType::E_None)
{
	//JointTargetLocation = FVector(0.f, 0.f, 0.f);
}

void UBasePlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (GetOwnCharacter())
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwnCharacter());
		if (Player)
		{
			bIsArmed = Player->GetIsArmed();
			bIsAiming = Player->GetIsAiming();
			bIsSprint = Player->GetIsSprint();
			Pitch = Player->GetBaseAimRotation().Pitch;
			WeaponType = Player->GetWeaponType();
			//LeftHandSocketTransform = Player->GetLeftHandSocketTransform();
			//JointTargetLocation = Player->JointTargetLocation;

			FRotator Rotation = Player->GetActorRotation();
			PlayerRotation = CalculateDirection(OwnerVelocity, Rotation);
		}
	}
}

void UBasePlayerAnimInstance::OnAttackPlayAM()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.f);
	}
}

void UBasePlayerAnimInstance::AnimNotify_AttackHit()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwnCharacter());
	if (Player)
	{
		Player->AttackCheck();
	}
}