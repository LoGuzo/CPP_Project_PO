// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DatabaseManager.h"
#include "QuestObjectiveDatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UQuestObjectiveDatabaseManager : public UDatabaseManager
{
	GENERATED_BODY()
	
public:
	UQuestObjectiveDatabaseManager();
	virtual ~UQuestObjectiveDatabaseManager();

protected:
	virtual void GetMyData() override;
};
