// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "AudioManager.h"
#include "SingletonManager.h"
#include "WidgetManager.h"
#include "ObjectPoolManager.h"
#include "QuestManager.h"
#include "DatabaseManager/BaseSkillDatabaseManager.h"
#include "DatabaseManager/ClassDatabaseManager.h"
#include "DatabaseManager/CunsumItemDatabaseManager.h"
#include "DatabaseManager/EquipItemDatabaseManager.h"
#include "DatabaseManager/ItemDatabaseManager.h"
#include "DatabaseManager/MontageDatabaseManager.h"
#include "DatabaseManager/MonsterDatabaseManager.h"
#include "DatabaseManager/PlayerSkillDatabaseManager.h"
#include "DatabaseManager/QuestDatabaseManager.h"
#include "DatabaseManager/QuestObjectiveDatabaseManager.h"
#include "DatabaseManager/QuestRewardDatabaseManager.h"
#include "DatabaseManager/SequenceDatabaseManager.h"
#include "DatabaseManager/SoundDatabaseManager.h"

UBaseGameInstance::UBaseGameInstance()
{
}

void UBaseGameInstance::Init()
{
	ManagerMap.Emplace(E_ManagerType::E_AudioManager, NewObject<UAudioManager>(this));
	ManagerMap.Emplace(E_ManagerType::E_WidgetManager, NewObject<UWidgetManager>(this));
	ManagerMap.Emplace(E_ManagerType::E_ObjectPoolManager, NewObject<UObjectPoolManager>(this));
	ManagerMap.Emplace(E_ManagerType::E_QuestManager, NewObject<UQuestManager>(this));
    AddDataToDatabase(E_ManagerType::E_ItemDatabaseManager, SingletonManager::GetInstance<UItemDatabaseManager>()->GetDataMap<FItemData>());
    AddDataToDatabase(E_ManagerType::E_ItemDatabaseManager, SingletonManager::GetInstance<UEquipItemDatabaseManager>()->GetDataMap<FEquipItemData>());
    AddDataToDatabase(E_ManagerType::E_ItemDatabaseManager, SingletonManager::GetInstance<UCunsumItemDatabaseManager>()->GetDataMap<FCunsumItemData>());
    AddDataToDatabase(E_ManagerType::E_MontageDatabaseManager, SingletonManager::GetInstance<UMontageDatabaseManager>()->GetDataMap<FMontageData>());
    AddDataToDatabase(E_ManagerType::E_ClassDatabaseManager, SingletonManager::GetInstance<UClassDatabaseManager>()->GetDataMap<FClassStatData>());
    AddDataToDatabase(E_ManagerType::E_MonsterDatabaseManager, SingletonManager::GetInstance<UMonsterDatabaseManager>()->GetDataMap<FMonsterStatData>());
    AddDataToDatabase(E_ManagerType::E_QuestDatabaseManager, SingletonManager::GetInstance<UQuestDatabaseManager>()->GetDataMap<FQuestData>());
    AddDataToDatabase(E_ManagerType::E_QuestObjectiveDatabaseManager, SingletonManager::GetInstance<UQuestObjectiveDatabaseManager>()->GetDataMap<FQuestObjective>());
    AddDataToDatabase(E_ManagerType::E_QuestRewardDatabaseManager, SingletonManager::GetInstance<UQuestRewardDatabaseManager>()->GetDataMap<FQuestReward>());
    AddDataToDatabase(E_ManagerType::E_SkillDatabaseManager, SingletonManager::GetInstance<UBaseSkillDatabaseManager>()->GetDataMap<FBaseSkillData>());
    AddDataToDatabase(E_ManagerType::E_SkillDatabaseManager, SingletonManager::GetInstance<UPlayerSkillDatabaseManager>()->GetDataMap<FSkillData>());
    AddDataToDatabase(E_ManagerType::E_SequenceDatabaseManager, SingletonManager::GetInstance<USequenceDatabaseManager>()->GetDataMap<FSequenceData>());
    AddDataToDatabase(E_ManagerType::E_SoundDatabaseManager, SingletonManager::GetInstance<USoundDatabaseManager>()->GetDataMap<FSoundData>());
}

void UBaseGameInstance::Shutdown()
{
	ManagerMap.Empty();
    DatabaseMap.Empty();
}

void UBaseGameInstance::AddDataToDatabase(E_ManagerType ManagerType, TMap<int32, TSharedPtr<FTableRowBase>> NewData)
{
    if (TMap<int32, TSharedPtr<FTableRowBase>>* ExistingData = DatabaseMap.Find(ManagerType))
    {
        for (const auto& Elem : NewData)
            ExistingData->Emplace(Elem.Key, Elem.Value);
    }
    else
    {
        DatabaseMap.Emplace(ManagerType, NewData);
    }
}