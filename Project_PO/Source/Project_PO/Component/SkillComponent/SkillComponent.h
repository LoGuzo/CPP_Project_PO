// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseActorComponent.h"
#include "../../MyStructureAll.h"
#include "SkillComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API USkillComponent : public UBaseActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class UStatComponent* StatComponent;

protected:
	UPROPERTY()
	TMap<int32, FBaseSkillData> SkillMap;

private:
	void SetSkillIsReady(int32 const& SkillID);

public:
	void SetStatComponent(class UStatComponent* _StatComponent) { StatComponent = _StatComponent; }

public:
	virtual void SetUpSkillMap(TArray<int32> SkillIDs);

	virtual void UseSkill(int32 const& SkillID);
};
