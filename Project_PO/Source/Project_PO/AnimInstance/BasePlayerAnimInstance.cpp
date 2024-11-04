// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerAnimInstance.h"
#include "Animation/AnimNotifies/AnimNotify_PlaySound.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "KismetAnimationLibrary.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Component/QuickSlotComponent/PotionQuickSlotComponent.h"

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
			PlayerRotation = UKismetAnimationLibrary::CalculateDirection(OwnerVelocity, Rotation);
		}
	}
}

void UBasePlayerAnimInstance::AnimNotify_PotionEnd()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwnCharacter());
	if (Player)
	{
		Player->GetPotionQuickSlotComponent()->SetUpQuickItem();
		Player->SetIsUseQuick(false);
	}
}