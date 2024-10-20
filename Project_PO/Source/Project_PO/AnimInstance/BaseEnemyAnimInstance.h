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

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool bIsWait;

	int32 AttackIndex;

public:
	bool GetIsWait() { return bIsWait; }
	void SetIsWait(bool _bIsWait) { bIsWait = _bIsWait; }

	void JumpToSection();
	FName GetAnimMontageName(int32 SectionIndex);

	virtual void PlaySome(FBaseSkillData* Data, float AttackSpeed) override;

	//Die 노티파이 정의
};
