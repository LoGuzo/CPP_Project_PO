// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterDatabaseManager.h"

UMonsterDatabaseManager::UMonsterDatabaseManager()
{
}

UMonsterDatabaseManager::~UMonsterDatabaseManager()
{
}

void UMonsterDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_MonsterStatData.DT_MonsterStatData"));
}