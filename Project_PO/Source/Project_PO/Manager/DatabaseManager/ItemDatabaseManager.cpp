/// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDatabaseManager.h"

UItemDatabaseManager::UItemDatabaseManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("/Game/DataTable/DT_ItemData.DT_ItemData"));

	MyData = DATA.Object;
}

UItemDatabaseManager::~UItemDatabaseManager()
{
}