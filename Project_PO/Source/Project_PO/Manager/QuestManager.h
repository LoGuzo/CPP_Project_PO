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

private:
	void GrantItem(int32 const& ItemID, int32 const& Amount, class APlayerCharacter* PlayerCharacter);
	void GrantExp(float const& Exp, class APlayerCharacter* PlayerCharacter);

public:
	void StartQuest(int32 const& QuestID);
	bool IsCompleteQuest(int32 const& QuestID);
	void CompleteObjective(int32 const& ObjectiveID, int32 const& Amount);
	void GrantRewards(int32 const& QuestID, class APlayerCharacter* PlayerCharacter);

};
