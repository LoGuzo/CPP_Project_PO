// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyBaseGameMode.h"
#include "../Character/Player/PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyBaseGameMode::AMyBaseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APlayerCharacter> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/Character/Player/BP_PlayCharacter.BP_PlayCharacter_C"));
	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


void AMyBaseGameMode::BeginPlay()
{
	Super::BeginPlay();
}