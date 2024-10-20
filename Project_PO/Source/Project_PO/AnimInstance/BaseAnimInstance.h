// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../MyStructureAll.h"
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

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

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
	UPROPERTY()
	class ABaseCharacter* OwnCharacter;

protected:
	FBaseSkillData* NowData;

private:
	void ColliderNotify();

protected:
	TSoftObjectPtr<UAnimMontage> FindMontage(int32 const& MontageID);

public:
	void SetOwnCharacter(class ABaseCharacter* _OwnCharacter) { OwnCharacter = _OwnCharacter; }

	class ABaseCharacter* GetOwnCharacter() { return OwnCharacter; }

	virtual void PlaySome(FBaseSkillData* Data, float AttackSpeed);

	UFUNCTION()
	void AnimNotify_Collider();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_Dead();
};
