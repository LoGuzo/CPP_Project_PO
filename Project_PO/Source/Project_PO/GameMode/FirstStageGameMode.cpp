// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstStageGameMode.h"
#include "../Controller/Player/BaseStagePlayerController.h"

AFirstStageGameMode::AFirstStageGameMode()
{
	FirstQuestID = 3000;
}

void AFirstStageGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayBackGound(TEXT("First Stage"));
}

void AFirstStageGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ABaseStagePlayerController* PlayerController = Cast<ABaseStagePlayerController>(NewPlayer);
	if (PlayerController)
		PlayerController->SetUpWeaponSelectWidget();
}