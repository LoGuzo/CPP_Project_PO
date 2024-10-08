// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../MyStructureAll.h"
#include "QuestManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UQuestManager : public UObject
{
	GENERATED_BODY()
	
private:
	TMap<int32, TWeakPtr<FQuestData>> NowQuests;

public:
	void StartQuest(int32 const& QuestID);
	void CompleteQuest(int32 const& QuestID);
	void GrantRewards(int32 const& QuestID);
};
