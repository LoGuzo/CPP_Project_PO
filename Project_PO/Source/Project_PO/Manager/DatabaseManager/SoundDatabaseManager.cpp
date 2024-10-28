// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundDatabaseManager.h"

USoundDatabaseManager::USoundDatabaseManager()
{
}

USoundDatabaseManager::~USoundDatabaseManager()
{
}

void USoundDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_SoundCueData.DT_SoundCueData"));
}
