// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../MyStructureAll.h"
#include "QuestManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestClear, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectiveUpdated, int32);

UCLASS()
class PROJECT_PO_API UQuestManager : public UObject
{
	GENERATED_BODY()

private:
	TMap<int32, TWeakPtr<FQuestData>> NowQuests;

public:
	FOnQuestClear OnQuestClear;
	FOnQuestUpdated OnQuestUpdated;
	FOnObjectiveUpdated OnObjectiveUpdated;

private:
	void GrantItem(int32 const& ItemID, int32 const& Amount, class APlayerCharacter* PlayerCharacter);
	void GrantExp(float const& Exp, class APlayerCharacter* PlayerCharacter);
	void CompleteObjective(int32 const& ObjectiveID, int32 const& TargetID, int32 const& Amount);
	void SetUpQuestClearWidget(int32 const& RewardID);

public:
	void StartQuest(int32 const& QuestID);
	bool IsCompleteQuest(int32 const& QuestID);
	void CheckingObjective(int32 const& TargetID, int32 const& Amount);
	void GrantRewards(int32 const& QuestID, class APlayerCharacter* PlayerCharacter);
};
