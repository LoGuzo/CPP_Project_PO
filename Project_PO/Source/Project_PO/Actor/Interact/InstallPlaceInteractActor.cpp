// Fill out your copyright notice in the Description page of Project Settings.


#include "InstallPlaceInteractActor.h"
#include "../../Character/Player/PlayerCharacter.h"
#include "../../Component/InteractionComponent.h"

AInstallPlaceInteractActor::AInstallPlaceInteractActor()
	: bIsInstall(true)
{
}

void AInstallPlaceInteractActor::Interact(AActor* PlayerCharacter)
{
	if (bIsInstall)
	{
		APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(PlayerCharacter);
		if (playerCharacter)
		{
			playerCharacter->GetInteractionComponent()->InstallObject(GetActorLocation(), GetActorRotation());
			bIsInstall = false;
		}
	}
}