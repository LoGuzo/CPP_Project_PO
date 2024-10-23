// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTriggerBox.h"
#include "LevelSequencePlayer.h"
#include "../Controller/Player/BasePlayerController.h"
#include "../GameMode/MyBaseGameMode.h"

ABaseTriggerBox::ABaseTriggerBox()
	: ActiveCnt(0)
	, TimerTime(0.f)
	, CurActiveCnt(0)
	, bIsFailed(false)
{

}

void ABaseTriggerBox::SetUpTrigger()
{
	bIsFailed = false;

	SpawnMonster();
	SetUpTimer(TimerTime);
}

void ABaseTriggerBox::QuestClear()
{
	if(!bIsFailed)
		TearDownTrigger();
}

void ABaseTriggerBox::QuestFailed()
{
	bIsFailed = true;
	TearDownTrigger();
}

void ABaseTriggerBox::TearDownTrigger()
{
	GetWorld()->GetTimerManager().ClearTimer(RemainTimer);
	AddRemoveWidget(TEXT("BossHp"));

	DeSpawnMonster();

	GetWorld()->GetTimerManager().SetTimer(RemainTimer, this, &ABaseTriggerBox::SetLevelSequence, 10.f, false);
	SetUpTimer(10.f);
}

void ABaseTriggerBox::SetUpTimer(float const& Time)
{
	AMyBaseGameMode* GameMode = Cast<AMyBaseGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		TArray<class ABasePlayerController*> PlayerControllers = GameMode->GetPlayerControllers();
		for (ABasePlayerController* PlayerController : PlayerControllers)
		{
			PlayerController->SetUpTimerWidget(Time);
		}
	}
}

void ABaseTriggerBox::AddRemoveWidget(FString const& WidgetName)
{
	AMyBaseGameMode* GameMode = Cast<AMyBaseGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
		GameMode->AddRemoveControllerWidget(WidgetName);
}

void ABaseTriggerBox::SetLevelSequence()
{
	if (HasAuthority())
	{
		AddRemoveWidget(TEXT("Timer"));

		CurActiveCnt = 0.f;

		OnActorBeginOverlap.AddDynamic(this, &ABaseTriggerBox::OnOverlapBegin);

		AMyBaseGameMode* GameMode = Cast<AMyBaseGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->PlaySequence(8001);
			FTimerHandle Timer;
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABaseTriggerBox::Teleport, 2.f, false);
		}
	}
}

void ABaseTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (HasAuthority())
	{
		if (!OtherActor)
			return;

		if (OtherActor->ActorHasTag("Player"))
			CurActiveCnt++;

		if (CurActiveCnt == ActiveCnt)
		{
			SetUpTrigger();
			OnActorBeginOverlap.RemoveDynamic(this, &ABaseTriggerBox::OnOverlapBegin);
		}
	}
}

void ABaseTriggerBox::Teleport()
{
	if (HasAuthority())
	{
		AMyBaseGameMode* GameMode = Cast<AMyBaseGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			TArray<class ABasePlayerController*> PlayerControllers = GameMode->GetPlayerControllers();
			for (ABasePlayerController* PlayerController : PlayerControllers)
			{
				PlayerController->GetPawn()->SetActorLocation(TeleportLocation);
			}
		}
	}
}

void ABaseTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
		OnActorBeginOverlap.AddDynamic(this, &ABaseTriggerBox::OnOverlapBegin);
}