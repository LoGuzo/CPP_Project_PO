// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestDatabaseManager.h"

UQuestDatabaseManager::UQuestDatabaseManager()
{
}

UQuestDatabaseManager::~UQuestDatabaseManager()
{
}

void UQuestDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_QuestData.DT_QuestData"));
}
