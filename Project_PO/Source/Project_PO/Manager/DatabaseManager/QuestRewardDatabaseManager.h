// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DatabaseManager.h"
#include "QuestRewardDatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UQuestRewardDatabaseManager : public UDatabaseManager
{
	GENERATED_BODY()
	
public:
	UQuestRewardDatabaseManager();
	virtual ~UQuestRewardDatabaseManager();

protected:
	virtual void GetMyData() override;
};
