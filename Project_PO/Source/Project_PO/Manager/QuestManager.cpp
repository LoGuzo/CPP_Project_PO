// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"
#include "BaseGameInstance.h"

void UQuestManager::StartQuest(int32 const& QuestID)
{
	if (NowQuests.Contains(QuestID))
		return;

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FQuestData> QuestData = GameInstance->GetDatabaseMap<FQuestData>(E_ManagerType::E_QuestDatabaseManager, QuestID);
		if (QuestData.IsValid())
			NowQuests.Emplace(QuestID, QuestData);
	}
}

void UQuestManager::CompleteQuest(int32 const& QuestID)
{
	if (!NowQuests.Contains(QuestID))
		return;

	TWeakPtr<FQuestData> WeakQuestData = NowQuests.FindRef(QuestID);
	if (TSharedPtr<FQuestData> QuestData = WeakQuestData.Pin())
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			for (int32 const& ObjectiveID : QuestData->ObjectiveIDs)
			{
				TWeakPtr<FQuestObjective> ObjectiveData = GameInstance->GetDatabaseMap<FQuestObjective>(E_ManagerType::E_QuestObjectiveDatabaseManager, ObjectiveID);
				if (ObjectiveData.IsValid())
				{
					if (ObjectiveData.Pin()->bIsComplete)
						continue;
				}
			}
		}
	}
}

void UQuestManager::GrantRewards(int32 const& QuestID)
{
	if (!NowQuests.Contains(QuestID))
		return;
}
