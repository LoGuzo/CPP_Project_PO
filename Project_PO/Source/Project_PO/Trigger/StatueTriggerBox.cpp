// Fill out your copyright notice in the Description page of Project Settings.


#include "StatueTriggerBox.h"
#include "../Actor/Spawner/InfiniteSpawnerActor.h"
#include "../Actor/Protect/StatueProtectActor.h"

AStatueTriggerBox::AStatueTriggerBox()
{
	TimerTime = 120.f;
}

void AStatueTriggerBox::SetUpTrigger()
{
	SetUpStatue();

	Super::SetUpTrigger();
	
	AddRemoveWidget(TEXT("BossHp"));
}

void AStatueTriggerBox::SpawnMonster()
{
	for (ABaseSpawnerActor* Spawner : Spawners)
	{
		AInfiniteSpawnerActor* InfiniteSpawner = Cast<AInfiniteSpawnerActor>(Spawner);
		if (InfiniteSpawner)
		{
			if (Target)
				InfiniteSpawner->SetTarget(Target);
			InfiniteSpawner->SetIsSpawn(true);
		}
	}
}

void AStatueTriggerBox::SetUpStatue()
{
	AStatueProtectActor* Statue = Cast<AStatueProtectActor>(Target);
	if (Statue)
		Statue->DelaySetUp();
}

void AStatueTriggerBox::DeSpawnMonster()
{
	for (ABaseSpawnerActor* Spawner : Spawners)
	{
		AInfiniteSpawnerActor* InfiniteSpawner = Cast<AInfiniteSpawnerActor>(Spawner);
		if (InfiniteSpawner)
		{
			InfiniteSpawner->SetIsSpawn(false);
			InfiniteSpawner->DeSpawnMonster();
		}
	}
}
