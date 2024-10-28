// Fill out your copyright notice in the Description page of Project Settings.


#include "BossTriggerBox.h"
#include "LevelSequencePlayer.h"
#include "../Actor/Spawner/BossSpawnerActor.h"

ABossTriggerBox::ABossTriggerBox()
{
	TimerTime = 600.f;
}

void ABossTriggerBox::SpawnMonster()
{
	for (ABaseSpawnerActor* Spawner : Spawners)
	{
		Spawner->SetOwnerTrigger(this);
		Spawner->SpawnMonster();
	}
}

void ABossTriggerBox::DeSpawnMonster()
{
	for (ABaseSpawnerActor* Spawner : Spawners)
	{
		Spawner->DeSpawnMonster();
		Spawner->SetOwnerTrigger(nullptr);
	}
}

void ABossTriggerBox::SetUpTrigger()
{
	Super::SetUpTrigger();

	AddRemoveWidget(TEXT("BossHp"));

	GetWorld()->GetTimerManager().SetTimer(RemainTimer, this, &ABossTriggerBox::QuestFailed, TimerTime, false);
}

void ABossTriggerBox::SetLevelSequence()
{
	ULevelSequencePlayer* SequencePlayer = GetPlaySequence(SequenceID);
	if(SequencePlayer)
	{
		SequencePlayer->OnFinished.AddDynamic(this, &ABossTriggerBox::SetUpTrigger);
	}
}