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
	
public:
	UBaseAnimInstance();

private:
	class UCharacterMovementComponent* MovementComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MovementData, Meta = (AllowPrivateAccess = true))
	bool bIsFalling;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MovementData, Meta = (AllowPrivateAccess = true))
	bool ShouldMove;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MovementData, Meta = (AllowPrivateAccess = true))
	float GroundSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MovementData, Meta = (AllowPrivateAccess = true))
	FVector OwnerVelocity;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY()
	class ACharacter* OwnCharacter;

public:
	UFUNCTION()
	void SetOwnCharacter(class ACharacter* _OwnCharacter) { OwnCharacter = _OwnCharacter; }

	UFUNCTION()
	class ACharacter* GetOwnCharacter() { return OwnCharacter; }

	void PlayMontage(TSoftObjectPtr<UAnimMontage> Montage, float AttackSpeed);

	UFUNCTION()
	void AnimNotify_AttackEnd();
};
