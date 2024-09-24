// Fill out your copyright notice in the Description page of Project Settings.


#include "ClassDatabaseManager.h"

UClassDatabaseManager::UClassDatabaseManager()
{
}

UClassDatabaseManager::~UClassDatabaseManager()
{
}

void UClassDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_ClassStatData.DT_ClassStatData"));
}
