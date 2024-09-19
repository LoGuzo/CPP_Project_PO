// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "WidgetManager.h"
#include "DatabaseManager/ItemDatabaseManager.h"
#include "DatabaseManager/EquipItemDatabaseManager.h"
#include "DatabaseManager/CunsumItemDatabaseManager.h"

UBaseGameInstance::UBaseGameInstance()
{
}

void UBaseGameInstance::Init()
{
	ManagerMap.Emplace(E_ManagerType::E_WidgetManager, NewObject<UWidgetManager>());
    AddDataToDatabase(E_ManagerType::E_ItemDatabaseManager, UItemDatabaseManager::GetDataMap<FItemData>());
    AddDataToDatabase(E_ManagerType::E_ItemDatabaseManager, UEquipItemDatabaseManager::GetDataMap<FEquipItemData>());
    AddDataToDatabase(E_ManagerType::E_ItemDatabaseManager, UCunsumItemDatabaseManager::GetDataMap<FCunsumItemData>());
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