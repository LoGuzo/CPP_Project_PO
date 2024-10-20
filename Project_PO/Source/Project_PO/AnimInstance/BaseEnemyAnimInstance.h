// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAnimInstance.h"
#include "BaseEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBaseEnemyAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UBaseEnemyAnimInstance();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool bIsReady;

	int32 AttackIndex;

public:
	bool GetIsReady() { return bIsReady; }
	void SetIsReady(bool _bIsReady) { bIsReady = _bIsReady; }

	void JumpToSection();
	FName GetAnimMontageName(int32 SectionIndex);

	virtual void PlaySome(FBaseSkillData* Data, float AttackSpeed) override;

	UFUNCTION()
	void AnimNotify_Ready();
};
