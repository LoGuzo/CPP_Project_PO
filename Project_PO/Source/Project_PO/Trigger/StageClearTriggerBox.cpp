// Fill out your copyright notice in the Description page of Project Settings.


#include "StageClearTriggerBox.h"
#include "LevelSequencePlayer.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Controller/Player/BaseStagePlayerController.h"
#include "../GameMode/BaseStageGameMode.h"

AStageClearTriggerBox::AStageClearTriggerBox()
{
}

void AStageClearTriggerBox::SetUpTrigger()
{
	SetStateAllPlayer(true);
}

void AStageClearTriggerBox::SetLevelSequence()
{
	ULevelSequencePlayer* SequencePlayer = GetPlaySequence(SequenceID);
	if (SequencePlayer)
	{
		SetStateAllPlayer(false);
		SequencePlayer->OnFinished.Clear();
		SequencePlayer->OnFinished.AddDynamic(this, &AStageClearTriggerBox::SetUpTrigger);
	}
}

void AStageClearTriggerBox::SetStateAllPlayer(bool const& bState)
{
	ABaseStageGameMode* GameMode = Cast<ABaseStageGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->PlayBackGound(SoundName);

		TArray<ABaseStagePlayerController*> PlayerControllers = GameMode->GetPlayerControllers();
		for (ABaseStagePlayerController* PlayerController : PlayerControllers)
		{
			if (PlayerController)
			{
				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetPawn());
				if (PlayerCharacter)
					PlayerCharacter->SetActorState(bState);
			}
		}
	}
}