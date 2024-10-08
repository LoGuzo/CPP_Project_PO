// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DatabaseManager.h"
#include "QuestDatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UQuestDatabaseManager : public UDatabaseManager
{
	GENERATED_BODY()
	
public:
	UQuestDatabaseManager();
	virtual ~UQuestDatabaseManager();

protected:
	virtual void GetMyData() override;
};
