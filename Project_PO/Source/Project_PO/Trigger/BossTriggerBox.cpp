// Fill out your copyright notice in the Description page of Project Settings.


#include "BossTriggerBox.h"
#include "../Actor/Spawner/BossSpawnerActor.h"

void ABossTriggerBox::SpawnMonster()
{
	for (ABaseSpawnerActor* Spawner : Spawners)
	{
		Spawner->SpawnMonster();
	}

	AddRemoveWidget(TEXT("BossHp"));
}