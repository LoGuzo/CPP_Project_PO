// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyBaseGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/ObjectPoolManager.h"
#include "../Manager/QuestManager.h"

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
}

void AMyBaseGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	GetWorld()->GetTimerManager().SetTimer(ResetTimer, this, &AMyBaseGameMode::StartQuest, 1.f, false);
}

void AMyBaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		auto ObjectPoolManager = GameInstance->GetManager<UObjectPoolManager>(E_ManagerType::E_ObjectPoolManager);
		if (ObjectPoolManager)
		{
			FTransform Transform = FTransform();
			Transform.SetLocation(FVector(-670.f, -15369.f, -512.f));
			ObjectPoolManager->GetMonster(GetWorld(), E_MonsterType::E_Golem, Transform);
			Transform.SetLocation(FVector(-750.f, -16129.f, -730.f));
			ObjectPoolManager->GetMonster(GetWorld(), E_MonsterType::E_Mummy, Transform);
		}
	}
}

void AMyBaseGameMode::StartQuest()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		auto QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
		if (QuestManager)
		{
			QuestManager->StartQuest(3000);
		}
	}
}