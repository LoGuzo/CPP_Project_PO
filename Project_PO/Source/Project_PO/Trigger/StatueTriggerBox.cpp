// Fill out your copyright notice in the Description page of Project Settings.


#include "StatueTriggerBox.h"
#include "../Actor/Spawner/InfiniteSpawnerActor.h"
#include "../Actor/Protect/StatueProtectActor.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/QuestManager.h"

AStatueTriggerBox::AStatueTriggerBox()
{
	TimerTime = 120.f;
}

void AStatueTriggerBox::SetUpTrigger()
{
	SetUpStatue();

	Super::SetUpTrigger();
	
	AddRemoveWidget(TEXT("BossHp"));

	GetWorld()->GetTimerManager().SetTimer(RemainTimer, this, &AStatueTriggerBox::QuestClear, TimerTime, false);
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
			InfiniteSpawner->SetOwnerTrigger(this);
		}
	}
}

void AStatueTriggerBox::SetUpStatue()
{
	AStatueProtectActor* Statue = Cast<AStatueProtectActor>(Target);
	if (Statue)
	{
		Statue->OnDestruct.AddUObject(this, &AStatueTriggerBox::QuestFailed);
		Statue->SetState(true);
		Statue->DelaySetUp();
	}
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

void AStatueTriggerBox::QuestClear()
{
	Super::QuestClear();

	ClearBroadCast();
}

void AStatueTriggerBox::ClearBroadCast()
{
	AStatueProtectActor* Statue = Cast<AStatueProtectActor>(Target);
	if (Statue)
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			UQuestManager* QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
			if (QuestManager)
				QuestManager->CheckingObjective(Statue->GetActorID(), 1);
		}
	}
}