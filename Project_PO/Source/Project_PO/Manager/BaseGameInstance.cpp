// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "WidgetManager.h"
#include "DatabaseManager/ItemDatabaseManager.h"

UBaseGameInstance::UBaseGameInstance()
{
}

void UBaseGameInstance::Init()
{
	ManagerMap.Emplace(E_ManagerType::E_WidgetManager, NewObject<UWidgetManager>());
	ManagerMap.Emplace(E_ManagerType::E_ItemDatabaseManager, NewObject<UItemDatabaseManager>());
}

void UBaseGameInstance::Shutdown()
{
	ManagerMap.Empty();
}