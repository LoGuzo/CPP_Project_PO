// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../MyEnumClass.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	UBaseAnimInstance();

private:
	class UCharacterMovementComponent* MovementComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MovementData, Meta = (AllowPrivateAccess = true))
	bool IsFalling;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MovementData, Meta = (AllowPrivateAccess = true))
	bool ShouldMove;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MovementData, Meta = (AllowPrivateAccess = true))
	float GroundSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MovementData, Meta = (AllowPrivateAccess = true))
	FVector OwnerVelocity;

	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Type, Meta = (AllowPrivateAccess = true))
	E_WeaponType WeaponType;

	UPROPERTY()
	class ACharacter* OwnCharacter;
};
