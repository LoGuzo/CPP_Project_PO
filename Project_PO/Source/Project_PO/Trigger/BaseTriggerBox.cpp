// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTriggerBox.h"
#include "../Controller/Player/BasePlayerController.h"
#include "../GameMode/MyBaseGameMode.h"

ABaseTriggerBox::ABaseTriggerBox()
	: ActiveCnt(0)
	, TimerTime(0.f)
	, CurActiveCnt(0)
{

}

void ABaseTriggerBox::SetUpTrigger()
{
	SpawnMonster();
	SetUpTimer();
}

void ABaseTriggerBox::TearDownTrigger()
{
	GetWorld()->GetTimerManager().ClearTimer(RemainTimer);
	AddRemoveWidget(TEXT("BossHp"));

	Teleport();
	DeSpawnMonster();
}

void ABaseTriggerBox::SetUpTimer()
{
	GetWorld()->GetTimerManager().SetTimer(RemainTimer, this, &ABaseTriggerBox::TearDownTrigger, TimerTime, false);

	AMyBaseGameMode* GameMode = Cast<AMyBaseGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		TArray<class ABasePlayerController*> PlayerControllers = GameMode->GetPlayerControllers();
		for (ABasePlayerController* PlayerController : PlayerControllers)
		{
			PlayerController->SetUpTimerWidget(TimerTime);
		}
	}
}

void ABaseTriggerBox::AddRemoveWidget(FString const& WidgetName)
{
	AMyBaseGameMode* GameMode = Cast<AMyBaseGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
		GameMode->AddRemoveControllerWidget(WidgetName);
}

void ABaseTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (HasAuthority())
	{
		if (!OtherActor)
			return;

		if(OtherActor->ActorHasTag("Player"))
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