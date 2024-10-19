// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillComponent.h"
#include "MonsterSkillComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UMonsterSkillComponent : public USkillComponent
{
	GENERATED_BODY()
	
public:
	bool ChkSkillRange(AActor* _Target, int32& SkillID);
};
