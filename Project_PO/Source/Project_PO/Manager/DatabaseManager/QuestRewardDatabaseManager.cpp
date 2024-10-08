// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestRewardDatabaseManager.h"

UQuestRewardDatabaseManager::UQuestRewardDatabaseManager()
{
}

UQuestRewardDatabaseManager::~UQuestRewardDatabaseManager()
{
}

void UQuestRewardDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_QuestRewardData.DT_QuestRewardData"));
}
