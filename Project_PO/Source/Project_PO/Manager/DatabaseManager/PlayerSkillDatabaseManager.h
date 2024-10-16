// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSkillDatabaseManager.h"
#include "PlayerSkillDatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UPlayerSkillDatabaseManager : public UBaseSkillDatabaseManager
{
	GENERATED_BODY()
	
public:
	UPlayerSkillDatabaseManager();
	virtual ~UPlayerSkillDatabaseManager();

protected:
	virtual void GetMyData() override;
};
