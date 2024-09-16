// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerAnimInstance.h"
#include "../Character/Player/PlayerCharacter.h"

UBasePlayerAnimInstance::UBasePlayerAnimInstance()
	: WeaponType(E_WeaponType::E_None)
	, bIsArmed(false)
	, bIsAiming(false)
	, Pitch(0.f)
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
			Pitch = Player->GetBaseAimRotation().Pitch;
		}
	}
}
