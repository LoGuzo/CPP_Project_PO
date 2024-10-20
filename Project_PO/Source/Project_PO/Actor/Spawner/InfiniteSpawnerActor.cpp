// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteSpawnerActor.h"

AInfiniteSpawnerActor::AInfiniteSpawnerActor()
	: bIsSpawn(false)
	, SpawnInterval(0.f)
    , TimeSinceLastSpawn(0.f)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInfiniteSpawnerActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

    if (bIsSpawn)
    {
        TimeSinceLastSpawn += DeltaSeconds;

        if (TimeSinceLastSpawn >= SpawnInterval)
        {
            SpawnMonster();
            TimeSinceLastSpawn = 0.0f;
        }
    }
}