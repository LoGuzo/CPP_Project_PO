// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "../Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBaseAnimInstance::UBaseAnimInstance() 
	: OwnCharacter(nullptr)
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
		GroundSpeed = OwnerVelocity.Size();
		if (MovementComponent)
		{
			ShouldMove = GroundSpeed > 3.f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector;
			IsFalling = MovementComponent->IsFalling();
		}
	}
}
