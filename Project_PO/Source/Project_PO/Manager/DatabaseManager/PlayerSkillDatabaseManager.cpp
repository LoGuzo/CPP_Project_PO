// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillDatabaseManager.h"

UPlayerSkillDatabaseManager::UPlayerSkillDatabaseManager()
{
}

UPlayerSkillDatabaseManager::~UPlayerSkillDatabaseManager()
{
}

void UPlayerSkillDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_PlayerSkillData.DT_PlayerSkillData"));
}