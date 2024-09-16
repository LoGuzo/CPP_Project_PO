// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "../Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
		OwnCharacter = Cast<ACharacter>(GetOwningActor());
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
