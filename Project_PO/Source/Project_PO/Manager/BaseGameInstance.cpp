// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "WidgetManager.h"
#include "SingletonManager.h"
#include "DatabaseManager/CunsumItemDatabaseManager.h"
#include "DatabaseManager/ItemDatabaseManager.h"
#include "DatabaseManager/EquipItemDatabaseManager.h"
#include "DatabaseManager/MontageDatabaseManager.h"

UBaseGameInstance::UBaseGameInstance()
{
}

void UBaseGameInstance::Init()
{
	ManagerMap.Emplace(E_ManagerType::E_WidgetManager, NewObject<UWidgetManager>());
    AddDataToDatabase(E_ManagerType::E_ItemDatabaseManager, SingletonManager::GetInstance<UItemDatabaseManager>()->GetDataMap<FItemData>());
    AddDataToDatabase(E_ManagerType::E_ItemDatabaseManager, SingletonManager::GetInstance<UEquipItemDatabaseManager>()->GetDataMap<FEquipItemData>());
    AddDataToDatabase(E_ManagerType::E_ItemDatabaseManager, SingletonManager::GetInstance<UCunsumItemDatabaseManager>()->GetDataMap<FCunsumItemData>());
    AddDataToDatabase(E_ManagerType::E_MontageDatabaseManager, SingletonManager::GetInstance<UMontageDatabaseManager>()->GetDataMap<FMontageData>());
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