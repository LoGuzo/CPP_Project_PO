// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpawnTriggerBox.h"
#include "../Controller/Player/BasePlayerController.h"
#include "../GameMode/MyBaseGameMode.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/QuestManager.h"

ABaseSpawnTriggerBox::ABaseSpawnTriggerBox()
	: TimerTime(0.f)
{

}

void ABaseSpawnTriggerBox::QuestClear()
{
	TearDownTrigger();
}

void ABaseSpawnTriggerBox::QuestFailed()
{
	TearDownTrigger();
}

void ABaseSpawnTriggerBox::SetUpTrigger()
{
	SpawnMonster();
	SetUpTimer(TimerTime);
}

void ABaseSpawnTriggerBox::TearDownTrigger()
{
	GetWorld()->GetTimerManager().ClearTimer(RemainTimer);
	AddRemoveWidget(TEXT("BossHp"));

	DeSpawnMonster();

	GetWorld()->GetTimerManager().SetTimer(RemainTimer, this, &ABaseSpawnTriggerBox::SetReturnHome, 10.f, false);
	SetUpTimer(10.f);
}

void ABaseSpawnTriggerBox::SetUpTimer(float const& Time)
{
	AMyBaseGameMode* GameMode = Cast<AMyBaseGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
		GameMode->SetUpTimerWidget(Time);
}

void ABaseSpawnTriggerBox::AddRemoveWidget(FString const& WidgetName)
{
	AMyBaseGameMode* GameMode = Cast<AMyBaseGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
		GameMode->AddRemoveControllerWidget(WidgetName);
}

void ABaseSpawnTriggerBox::SetReturnHome()
{
	if (HasAuthority())
	{
		AddRemoveWidget(TEXT("Timer"));

		OnActorBeginOverlap.AddDynamic(this, &ABaseSpawnTriggerBox::OnOverlapBegin);

		GetPlaySequence(8001);

		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABaseSpawnTriggerBox::Teleport, 2.f, false);
	}
}

void ABaseSpawnTriggerBox::Teleport()
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