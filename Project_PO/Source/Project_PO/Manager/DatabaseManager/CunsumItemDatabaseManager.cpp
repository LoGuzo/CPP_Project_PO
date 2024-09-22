// Fill out your copyright notice in the Description page of Project Settings.


#include "CunsumItemDatabaseManager.h"

UCunsumItemDatabaseManager::UCunsumItemDatabaseManager()
{
}

UCunsumItemDatabaseManager::~UCunsumItemDatabaseManager()
{
}

void UCunsumItemDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_CunsumItemData.DT_CunsumItemData"));
}
