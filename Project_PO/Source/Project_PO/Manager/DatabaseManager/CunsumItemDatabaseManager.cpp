// Fill out your copyright notice in the Description page of Project Settings.


#include "CunsumItemDatabaseManager.h"

UCunsumItemDatabaseManager::UCunsumItemDatabaseManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("/Game/DataTable/DT_CunsumItemData.DT_CunsumItemData"));

	MyData = DATA.Object;
}

UCunsumItemDatabaseManager::~UCunsumItemDatabaseManager()
{
}
