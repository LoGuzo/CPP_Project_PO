// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceDatabaseManager.h"

USequenceDatabaseManager::USequenceDatabaseManager()
{
}

USequenceDatabaseManager::~USequenceDatabaseManager()
{
}

void USequenceDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_SequenceData.DT_SequenceData"));
}
