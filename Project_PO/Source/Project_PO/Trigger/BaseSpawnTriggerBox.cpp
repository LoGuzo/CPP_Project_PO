// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpawnTriggerBox.h"
#include "../Controller/Player/BaseStagePlayerController.h"
#include "../GameMode/BaseStageGameMode.h"
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
	ABaseStageGameMode* GameMode = Cast<ABaseStageGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
		GameMode->SetUpTimerWidget(Time);
}

void ABaseSpawnTriggerBox::AddRemoveWidget(FString const& WidgetName)
{
	ABaseStageGameMode* GameMode = Cast<ABaseStageGameMode>(GetWorld()->GetAuthGameMode());
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
		ABaseStageGameMode* GameMode = Cast<ABaseStageGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->PlayBackGound(SoundName);

			TArray<ABaseStagePlayerController*> PlayerControllers = GameMode->GetPlayerControllers();
			for (ABaseStagePlayerController* PlayerController : PlayerControllers)
			{
				PlayerController->GetPawn()->SetActorLocation(TeleportLocation);
			}
		}
	}
}