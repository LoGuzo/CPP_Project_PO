// Fill out your copyright notice in the Description page of Project Settings.


#include "MontageDatabaseManager.h"

UMontageDatabaseManager::UMontageDatabaseManager()
{
}

UMontageDatabaseManager::~UMontageDatabaseManager()
{
}

void UMontageDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_MontageData.DT_MontageData"));
}
