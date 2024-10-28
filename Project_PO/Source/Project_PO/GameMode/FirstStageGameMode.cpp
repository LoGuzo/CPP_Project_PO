// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstStageGameMode.h"
#include "../Controller/Player/BasePlayerController.h"

AFirstStageGameMode::AFirstStageGameMode()
{
	FirstQuestID = 3000;
}

void AFirstStageGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(NewPlayer);
	if (PlayerController)
		PlayerController->SetUpWeaponSelectWidget();
}