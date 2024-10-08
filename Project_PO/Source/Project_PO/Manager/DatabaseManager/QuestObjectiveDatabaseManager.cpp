// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestObjectiveDatabaseManager.h"

UQuestObjectiveDatabaseManager::UQuestObjectiveDatabaseManager()
{
}

UQuestObjectiveDatabaseManager::~UQuestObjectiveDatabaseManager()
{
}

void UQuestObjectiveDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_QuestObjectiveData.DT_QuestObjectiveData"));
}
