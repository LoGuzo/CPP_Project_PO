// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTriggerBox.h"

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