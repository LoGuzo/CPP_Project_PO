// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGunAnimInstance.h"

UBaseGunAnimInstance::UBaseGunAnimInstance()
{
}

void UBaseGunAnimInstance::OnGunAttackPlayAM()
{
	if (!Montage_IsPlaying(GunAttackMontage))
	{
		Montage_Play(GunAttackMontage, 1.f);
	}
}
