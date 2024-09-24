// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DatabaseManager.h"
#include "MonsterDatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UMonsterDatabaseManager : public UDatabaseManager
{
	GENERATED_BODY()
	
public:
	UMonsterDatabaseManager();
	virtual ~UMonsterDatabaseManager();

protected:
	virtual void GetMyData() override;
};
