// Fill out your copyright notice in the Description page of Project Settings.


#include "BossTriggerBox.h"
#include "../Actor/Spawner/BossSpawnerActor.h"

ABossTriggerBox::ABossTriggerBox()
{
	TimerTime = 600.f;
}

void ABossTriggerBox::SpawnMonster()
{
	for (ABaseSpawnerActor* Spawner : Spawners)
	{
		Spawner->SpawnMonster();
	}
}

void ABossTriggerBox::DeSpawnMonster()
{
	for (ABaseSpawnerActor* Spawner : Spawners)
	{
		Spawner->DeSpawnMonster();
	}
}

void ABossTriggerBox::SetUpTrigger()
{
	Super::SetUpTrigger();

	AddRemoveWidget(TEXT("BossHp"));
}
