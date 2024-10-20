// Fill out your copyright notice in the Description page of Project Settings.


#include "StatueTriggerBox.h"
#include "../Actor/Spawner/InfiniteSpawnerActor.h"

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

void AStatueTriggerBox::DeSpawnMonster()
{
	for (ABaseSpawnerActor* Spawner : Spawners)
	{
		AInfiniteSpawnerActor* InfiniteSpawner = Cast<AInfiniteSpawnerActor>(Spawner);
		if (InfiniteSpawner)
			InfiniteSpawner->SetIsSpawn(false);
	}
}
