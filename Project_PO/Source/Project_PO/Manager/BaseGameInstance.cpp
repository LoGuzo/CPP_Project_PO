// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "SingletonManager.h"
#include "WidgetManager.h"
#include "ObjectPoolManager.h"
#include "DatabaseManager/CunsumItemDatabaseManager.h"
#include "DatabaseManager/ClassDatabaseManager.h"
#include "DatabaseManager/ItemDatabaseManager.h"
#include "DatabaseManager/EquipItemDatabaseManager.h"
#include "DatabaseManager/MontageDatabaseManager.h"
#include "DatabaseManager/MonsterDatabaseManager.h"
#include "DatabaseManager/QuestDatabaseManager.h"
#include "DatabaseManager/QuestObjectiveDatabaseManager.h"
#include "DatabaseManager/QuestRewardDatabaseManager.h"

UBaseGameInstance::UBaseGameInstance()
{
}

void UBaseGameInstance::Init()
{
	ManagerMap.Emplace(E_ManagerType::E_WidgetManager, NewObject<UWidgetManager>());
	ManagerMap.Emplace(E_ManagerType::E_ObjectPoolManager, NewObject<UObjectPoolManager>());
    AddDataToDatabase(E_ManagerType::E_ItemDatabaseManager, SingletonManager::GetInstance<UItemDatabaseManager>()->GetDataMap<FItemData>());
    AddDataToDatabase(E_ManagerType::E_ItemDatabaseManager, SingletonManager::GetInstance<UEquipItemDatabaseManager>()->GetDataMap<FEquipItemData>());
    AddDataToDatabase(E_ManagerType::E_ItemDatabaseManager, SingletonManager::GetInstance<UCunsumItemDatabaseManager>()->GetDataMap<FCunsumItemData>());
    AddDataToDatabase(E_ManagerType::E_MontageDatabaseManager, SingletonManager::GetInstance<UMontageDatabaseManager>()->GetDataMap<FMontageData>());
    AddDataToDatabase(E_ManagerType::E_ClassDatabaseManager, SingletonManager::GetInstance<UClassDatabaseManager>()->GetDataMap<FClassStatData>());
    AddDataToDatabase(E_ManagerType::E_MonsterDatabaseManager, SingletonManager::GetInstance<UMonsterDatabaseManager>()->GetDataMap<FMonsterStatData>());
    AddDataToDatabase(E_ManagerType::E_QuestDatabaseManager, SingletonManager::GetInstance<UQuestDatabaseManager>()->GetDataMap<FQuestData>());
    AddDataToDatabase(E_ManagerType::E_QuestObjectiveDatabaseManager, SingletonManager::GetInstance<UQuestObjectiveDatabaseManager>()->GetDataMap<FQuestObjective>());
    AddDataToDatabase(E_ManagerType::E_QuestRewardDatabaseManager, SingletonManager::GetInstance<UQuestRewardDatabaseManager>()->GetDataMap<FQuestReward>());
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