// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"
#include "BaseGameInstance.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Component/InventoryComponent.h"
#include "../Component/StatComponent/PlayerStatComponent.h"

void UQuestManager::StartQuest(int32 const& QuestID)
{
	if (NowQuests.Contains(QuestID))
		return;

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FQuestData> QuestData = GameInstance->GetDatabaseMap<FQuestData>(E_ManagerType::E_QuestDatabaseManager, QuestID);
		if (QuestData.IsValid())
		{
			if (QuestData.Pin()->QuestState == E_QuestState::E_Completed)
				return;

			if (TSharedPtr<FQuestData> questData = QuestData.Pin())
			{
				questData->QuestState = E_QuestState::E_InProgress;
				NowQuests.Emplace(QuestID, questData);
			}
		}
	}
}

bool UQuestManager::IsCompleteQuest(int32 const& QuestID)
{
	if (!NowQuests.Contains(QuestID))
		return false;

	TWeakPtr<FQuestData> QuestData = *NowQuests.Find(QuestID);
	if (QuestData.IsValid())
	{
		for (const int32& ObjectiveID : QuestData.Pin()->ObjectiveIDs)
		{
			UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
			if (GameInstance)
			{
				TWeakPtr<FQuestObjective> ObjectiveData = GameInstance->GetDatabaseMap<FQuestObjective>(E_ManagerType::E_QuestObjectiveDatabaseManager, ObjectiveID);
				if (ObjectiveData.IsValid())
				{
					if (!ObjectiveData.Pin()->bIsComplete)
						return false;
				}
			}
		}
		if (TSharedPtr<FQuestData> questData = QuestData.Pin())
		{
			if (questData.IsValid())
			{
				questData->QuestState = E_QuestState::E_Completed;
				return true;
			}
		}
	}

	return false;
}

void UQuestManager::CompleteObjective(int32 const& ObjectiveID, int32 const& Amount)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FQuestObjective> ObjectiveData = GameInstance->GetDatabaseMap<FQuestObjective>(E_ManagerType::E_QuestObjectiveDatabaseManager, ObjectiveID);
		if (ObjectiveData.IsValid())
		{
			if (ObjectiveData.Pin()->bIsComplete)
				return;

			if (TSharedPtr<FQuestObjective> objectiveData = ObjectiveData.Pin())
			{
				if(objectiveData.IsValid())
					objectiveData->UpdateProgress(Amount);
			}
		}
	}
}

void UQuestManager::GrantRewards(int32 const& QuestID, class APlayerCharacter* PlayerCharacter)
{
	if (!NowQuests.Contains(QuestID))
		return;

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FQuestData> QuestData = NowQuests.FindRef(QuestID);
		if (QuestData.IsValid())
		{
			if (QuestData.Pin()->QuestState == E_QuestState::E_Completed)
			{
				TWeakPtr<FQuestReward> RewardData = GameInstance->GetDatabaseMap<FQuestReward>(E_ManagerType::E_QuestObjectiveDatabaseManager, QuestData.Pin()->RewardID);
				if (RewardData.IsValid())
				{
					for (const FRewardItem& RewardItem : RewardData.Pin()->ItemRewards)
					{
						if (PlayerCharacter)
							GrantItem(RewardItem.ItemID, RewardItem.Amount, PlayerCharacter);
					}
					GrantExp(RewardData.Pin()->AcquiredEXP, PlayerCharacter);
				}
			}
		}
	}
}

void UQuestManager::GrantItem(int32 const& ItemID, int32 const& Amount, class APlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			TWeakPtr<FItemData> ItemData = GameInstance->GetDatabaseMap<FItemData>(E_ManagerType::E_ItemDatabaseManager, ItemID);
			if (ItemData.IsValid())
				PlayerCharacter->GetInventoryComponent()->AddItem(ItemID, Amount, ItemData.Pin()->ItemType);
		}
	}
}

void UQuestManager::GrantExp(float const& Exp, APlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
		if (UPlayerStatComponent* PlayerStatComponent = PlayerCharacter->GetStatComponent<UPlayerStatComponent>())
			PlayerStatComponent->TakedExp(Exp);
}
