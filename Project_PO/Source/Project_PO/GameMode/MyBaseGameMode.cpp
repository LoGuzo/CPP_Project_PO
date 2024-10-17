// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyBaseGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "../Character/Enemy/EnemyCharacter.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Controller/Player/BasePlayerController.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/ObjectPoolManager.h"
#include "../Manager/QuestManager.h"

AMyBaseGameMode::AMyBaseGameMode()
	: bIsHavingFirstPlayer(false)
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

	InitPlayerController(NewPlayer);

	GetWorld()->GetTimerManager().SetTimer(ResetTimer, this, &AMyBaseGameMode::StartQuest, 1.f, false);
}

void AMyBaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	BindingReward();

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
			AEnemyCharacter* Enemy = ObjectPoolManager->GetMonster(GetWorld(), E_MonsterType::E_Mummy, Transform);
			if (Enemy)
				Enemy->SetTarget(PlayerControllers[0]->GetPawn());
		}
	}
}

void AMyBaseGameMode::InitPlayerController(APlayerController* NewPlayer)
{
	if (NewPlayer)
	{
		if (!bIsHavingFirstPlayer)
		{
			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(NewPlayer->GetPawn());
			if (PlayerCharacter)
			{
				PlayerCharacter->SetIsFirstPlayer(true);
				bIsHavingFirstPlayer = true;
			}
		}
		ABasePlayerController* PlayerController = Cast<ABasePlayerController>(NewPlayer);
		if(PlayerController)
			PlayerControllers.Emplace(PlayerController);
	}
}

void AMyBaseGameMode::StartQuest()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		auto QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
		if (QuestManager)
			QuestManager->StartQuest(3000);
	}
}

void AMyBaseGameMode::BindingReward()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		UQuestManager* QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
		if (QuestManager)
			QuestManager->OnQuestClear.AddUObject(this, &AMyBaseGameMode::GrantReward);
	}
}

void AMyBaseGameMode::GrantReward(int32 QuestID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		UQuestManager* QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
		if (QuestManager)
		{
			for (ABasePlayerController* PlayerController : PlayerControllers)
			{
				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetPawn());
				if (PlayerCharacter)
					QuestManager->GrantRewards(QuestID, PlayerCharacter);
			}
		}
	}
}
