// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportTriggerBox.h"
#include "../Character/Player/PlayerCharacter.h"

void ATeleportTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ATeleportTriggerBox::OnOverlapBegin);
}

void ATeleportTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
		if (PlayerCharacter)
			PlayerCharacter->SetActorLocation(PlayerCharacter->GetRespawnLocation());
	}
}