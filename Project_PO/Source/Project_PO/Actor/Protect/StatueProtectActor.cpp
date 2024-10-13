// Fill out your copyright notice in the Description page of Project Settings.


#include "StatueProtectActor.h"
#include "../../Component/StatComponent/MonsterStatComponent.h"

AStatueProtectActor::AStatueProtectActor()
{
	ActorID = 103;
}

void AStatueProtectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AStatueProtectActor::SetUpStatComponent()
{
	if (Statcomponent)
		Statcomponent->SetStat(ActorID);
}
