// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"
#include "BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Component/InventoryComponent.h"
#include "../Component/StatComponent/PlayerStatComponent.h"

void UQuestManager::StartQuest(int32 const& QuestID)
{
	if (NowQuests.Contains(QuestID))
		return;

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
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

				OnQuestUpdated.Broadcast(QuestID);
			}
		}
	}
}

bool UQuestManager::IsCompleteQuest(int32 const& QuestID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		TWeakPtr<FQuestData> QuestData = GameInstance->GetDatabaseMap<FQuestData>(E_ManagerType::E_QuestDatabaseManager, QuestID);
		if (QuestData.IsValid())
		{
			if (QuestData.Pin()->QuestState == E_QuestState::E_Completed)
				return true;

			for (const int32& ObjectiveID : QuestData.Pin()->ObjectiveIDs)
			{
				TWeakPtr<FQuestObjective> ObjectiveData = GameInstance->GetDatabaseMap<FQuestObjective>(E_ManagerType::E_QuestObjectiveDatabaseManager, ObjectiveID);
				if (ObjectiveData.IsValid())
				{
					if (!ObjectiveData.Pin()->bIsComplete)
						return false;
				}
			}

			if (TSharedPtr<FQuestData> questData = QuestData.Pin())
			{
				if (questData.IsValid())
				{
					if (questData->QuestState != E_QuestState::E_Completed)
						questData->QuestState = E_QuestState::E_Completed;

					if (NowQuests.Contains(QuestID))
					{
						if (QuestData.Pin()->NextQuestID != -1)
							StartQuest(QuestData.Pin()->NextQuestID);
						else
							OnQuestUpdated.Broadcast(-1);

						OnQuestClear.Broadcast(QuestID);

						//NowQuests.Remove(QuestID);
					}

					return true;
				}
			}
		}
	}
	return false;
}

void UQuestManager::CheckingObjective(int32 const& TargetID, int32 const& Amount)
{
	TArray<int32> QuestsToRemove;
	TArray<int32> QuestKeys;
	NowQuests.GenerateKeyArray(QuestKeys);

	for (int32 QuestID : QuestKeys)
	{
		TWeakPtr<FQuestData> WeakQuestData = NowQuests.FindRef(QuestID);

		if (WeakQuestData.IsValid())
		{
			for (const int32& ObjectiveID : WeakQuestData.Pin()->ObjectiveIDs)
			{
				CompleteObjective(ObjectiveID, TargetID, Amount);
			}

			if (IsCompleteQuest(QuestID))
				QuestsToRemove.Add(QuestID);
		}
	}

	for (int32 QuestID : QuestsToRemove)
	{
		NowQuests.Remove(QuestID);
	}
}

void UQuestManager::CompleteObjective(int32 const& ObjectiveID, int32 const& TargetID, int32 const& Amount)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		TWeakPtr<FQuestObjective> ObjectiveData = GameInstance->GetDatabaseMap<FQuestObjective>(E_ManagerType::E_QuestObjectiveDatabaseManager, ObjectiveID);
		if (ObjectiveData.IsValid())
		{
			if (ObjectiveData.Pin()->bIsComplete)
				return;
			if (ObjectiveData.Pin()->TargetID != TargetID)
				return;

			if (TSharedPtr<FQuestObjective> objectiveData = ObjectiveData.Pin())
			{
				if(objectiveData.IsValid())
					objectiveData->UpdateProgress(Amount);

				OnObjectiveUpdated.Broadcast(ObjectiveID);
			}
		}
	}
}

void UQuestManager::GrantRewards(int32 const& QuestID, class APlayerCharacter* PlayerCharacter)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		TWeakPtr<FQuestData> QuestData = GameInstance->GetDatabaseMap<FQuestData>(E_ManagerType::E_QuestDatabaseManager, QuestID);
		if (QuestData.IsValid())
		{
			if (QuestData.Pin()->QuestState == E_QuestState::E_Completed)
			{
				if (QuestData.Pin()->RewardID == -1)
					return;

				TWeakPtr<FQuestReward> RewardData = GameInstance->GetDatabaseMap<FQuestReward>(E_ManagerType::E_QuestRewardDatabaseManager, QuestData.Pin()->RewardID);
				if (RewardData.IsValid())
				{
					for (const FRewardItem& RewardItem : RewardData.Pin()->ItemRewards)
					{
						if (PlayerCharacter)
						{
							if (RewardItem.bIsIndividualReward)
							{
								if (!PlayerCharacter->GetIsFirstPlayer())
									continue;
							}
							GrantItem(RewardItem.ItemID, RewardItem.Amount, PlayerCharacter);
						}
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
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
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
