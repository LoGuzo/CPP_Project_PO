// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipItemDatabaseManager.h"

UEquipItemDatabaseManager::UEquipItemDatabaseManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("/Game/DataTable/DT_EquipItemData.DT_EquipItemData"));

	MyData = DATA.Object;
}

UEquipItemDatabaseManager::~UEquipItemDatabaseManager()
{
}
