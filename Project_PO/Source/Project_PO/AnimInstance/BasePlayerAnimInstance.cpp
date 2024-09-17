// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerAnimInstance.h"
#include "../Character/Player/PlayerCharacter.h"

UBasePlayerAnimInstance::UBasePlayerAnimInstance()
	: bIsArmed(false)
	, bIsAiming(false)
	, Pitch(0.f)
	, WeaponType(E_WeaponType::E_None)
{
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

			FRotator Rotation = Player->GetActorRotation();
			PlayerRotation = CalculateDirection(OwnerVelocity, Rotation);
		}
	}
}
