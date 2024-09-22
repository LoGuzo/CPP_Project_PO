/// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDatabaseManager.h"

UItemDatabaseManager::UItemDatabaseManager()
{

}

UItemDatabaseManager::~UItemDatabaseManager()
{
}

void UItemDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_ItemData.DT_ItemData"));
}
