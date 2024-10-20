// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTriggerBox.h"
#include "../GameMode/MyBaseGameMode.h"

ABaseTriggerBox::ABaseTriggerBox()
	: ActiveCnt(0)
	, CurActiveCnt(0)
{

}

void ABaseTriggerBox::SetUpTrigger()
{
	SpawnMonster();
	OnActorBeginOverlap.RemoveDynamic(this, &ABaseTriggerBox::OnOverlapBegin);
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
			SetUpTrigger();
	}
}

void ABaseTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ABaseTriggerBox::OnOverlapBegin);
}