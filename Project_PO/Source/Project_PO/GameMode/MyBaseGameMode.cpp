// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyBaseGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/DatabaseManager/ItemDatabaseManager.h"

AMyBaseGameMode::AMyBaseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APlayerCharacter> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/Character/Player/BP_PlayCharacter.BP_PlayCharacter_C"));
	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMyBaseGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	auto MyInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (MyInstance)
	{
		DatabaseMap.Emplace(E_ManagerType::E_ItemDatabaseManager, MyInstance->GetManager<UItemDatabaseManager>(E_ManagerType::E_ItemDatabaseManager)->GetDataMap());
	}
}


void AMyBaseGameMode::BeginPlay()
{
	Super::BeginPlay();
}