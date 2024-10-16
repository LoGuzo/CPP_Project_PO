// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DatabaseManager.h"
#include "BaseSkillDatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBaseSkillDatabaseManager : public UDatabaseManager
{
	GENERATED_BODY()
	
public:
	UBaseSkillDatabaseManager();
	virtual ~UBaseSkillDatabaseManager();

protected:
	virtual void GetMyData() override;
};
