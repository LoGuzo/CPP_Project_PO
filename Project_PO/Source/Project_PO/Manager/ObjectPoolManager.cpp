// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolManager.h"
#include "FactoryManager.h"
#include "SingletonManager.h"
#include "../Character/Enemy/EnemyCharacter.h"

AEnemyCharacter* UObjectPoolManager::GetMonster(E_MonsterType Type)
{
	for (int32 i = 0; i < AvailableMonsters.Num(); ++i)
	{
		if (!AvailableMonsters[i]/*!AvailableMonsters[i]->IsInUse && AvailableMonsters[i]->GetType == Type*/)
		{
			AEnemyCharacter* Monster = AvailableMonsters[i];
			Monster->SetState(true);
			//Monster->IsInUse = true;
			AvailableMonsters.RemoveAt(i);
			return Monster;
		}
	}
	AEnemyCharacter* NewMonster = SingletonManager::GetInstance<UFactoryManager>()->MonsterFactory(Type);
	AvailableMonsters.Add(NewMonster);
	return nullptr;
}

void UObjectPoolManager::ReleaseMonster(AEnemyCharacter* Monster)
{
	if (Monster)
	{
		Monster->SetState(false);
		//Monster->IsInUse = false;
		AvailableMonsters.Add(Monster);
	}
}