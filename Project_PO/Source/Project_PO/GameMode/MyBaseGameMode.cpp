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
	, FirstQuestID(-1)
{
	static ConstructorHelpers::FClassFinder<APlayerCharacter> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/Character/Player/BP_PlayCharacter.BP_PlayCharacter_C"));
	if (PlayerPawnBPClass.Succeeded())
		DefaultPawnClass = PlayerPawnBPClass.Class;

	PlayerControllerClass = ABasePlayerController::StaticClass();
}

void AMyBaseGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AMyBaseGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	InitPlayerController(NewPlayer);
}

void AMyBaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	BindingReward();

	GetWorld()->GetTimerManager().SetTimer(ResetTimer, this, &AMyBaseGameMode::StartQuest, 1.f, false);
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
	if (FirstQuestID == -1)
		return;

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		auto QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
		if (QuestManager)
			QuestManager->StartQuest(FirstQuestID);
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
	if (QuestID == -1)
		return;

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
