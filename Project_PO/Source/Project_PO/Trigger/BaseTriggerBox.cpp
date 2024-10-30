// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTriggerBox.h"
#include "LevelSequencePlayer.h"
#include "../Controller/Player/BasePlayerController.h"
#include "../GameMode/BaseStageGameMode.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/QuestManager.h"

ABaseTriggerBox::ABaseTriggerBox()
	: ActiveCnt(0)
	, CurActiveCnt(0)
{

}

ULevelSequencePlayer* ABaseTriggerBox::GetPlaySequence(int32 const& _SequenceID)
{
	ABaseStageGameMode* GameMode = Cast<ABaseStageGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
		return GameMode->PlaySequence(_SequenceID);

	return nullptr;
}

void ABaseTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (HasAuthority())
	{
		if (!OtherActor)
			return;

		if (OtherActor->ActorHasTag("Player"))
			CurActiveCnt++;

		if (ActiveCnt <= CurActiveCnt)
		{
			CurActiveCnt = 0;

			SetLevelSequence();
			OnActorBeginOverlap.RemoveDynamic(this, &ABaseTriggerBox::OnOverlapBegin);
		}
	}
}

void ABaseTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
		OnActorBeginOverlap.AddDynamic(this, &ABaseTriggerBox::OnOverlapBegin);
}