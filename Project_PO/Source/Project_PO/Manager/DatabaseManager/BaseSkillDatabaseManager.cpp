// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSkillDatabaseManager.h"

UBaseSkillDatabaseManager::UBaseSkillDatabaseManager()
{
}

UBaseSkillDatabaseManager::~UBaseSkillDatabaseManager()
{
}

void UBaseSkillDatabaseManager::GetMyData()
{
	MyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_MonsterPatternData.DT_MonsterPatternData"));
}