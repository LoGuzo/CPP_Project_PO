// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipItemDatabaseManager.h"

UEquipItemDatabaseManager::UEquipItemDatabaseManager()
{
}

UEquipItemDatabaseManager::~UEquipItemDatabaseManager()
{
}

void UEquipItemDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_EquipItemData.DT_EquipItemData"));
}

