// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseStageGameMode.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "UObject/ConstructorHelpers.h"
#include "../Character/Enemy/EnemyCharacter.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Controller/Player/BaseStagePlayerController.h"
#include "../Manager/AudioManager.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/ObjectPoolManager.h"
#include "../Manager/QuestManager.h"

ABaseStageGameMode::ABaseStageGameMode()
	: bIsHavingFirstPlayer(false)
	, FirstQuestID(-1)
{
	static ConstructorHelpers::FClassFinder<APlayerCharacter> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/Character/Player/BP_PlayCharacter.BP_PlayCharacter_C"));
	if (PlayerPawnBPClass.Succeeded())
		DefaultPawnClass = PlayerPawnBPClass.Class;

	PlayerControllerClass = ABaseStagePlayerController::StaticClass();
}

void ABaseStageGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ABaseStageGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	InitPlayerController(NewPlayer);
}

void ABaseStageGameMode::BeginPlay()
{
	Super::BeginPlay();

	BindingReward();

	GetWorld()->GetTimerManager().SetTimer(ResetTimer, this, &ABaseStageGameMode::StartQuest, 1.f, false);
}

void ABaseStageGameMode::InitPlayerController(APlayerController* NewPlayer)
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
		ABaseStagePlayerController* PlayerController = Cast<ABaseStagePlayerController>(NewPlayer);
		if(PlayerController)
			PlayerControllers.Emplace(PlayerController);
	}
}

void ABaseStageGameMode::StartQuest()
{
	if (FirstQuestID == -1)
		return;

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		UQuestManager* QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
		if (QuestManager)
			QuestManager->StartQuest(FirstQuestID);
	}
}

void ABaseStageGameMode::BindingReward()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		UQuestManager* QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
		if (QuestManager)
			QuestManager->OnQuestClear.AddUObject(this, &ABaseStageGameMode::GrantReward);
	}
}

void ABaseStageGameMode::GrantReward(int32 QuestID)
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

void ABaseStageGameMode::PlayBackGound(FString const& SoundName)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		UAudioManager* AudioManager = GameInstance->GetManager<UAudioManager>(E_ManagerType::E_AudioManager);
		if (AudioManager)
			AudioManager->PlayBackgroundMusic(GetWorld(), SoundName);
	}
}

void ABaseStageGameMode::AddRemoveControllerWidget(FString const& WidgetName)
{
	GetWorld()->GetTimerManager().ClearTimer(ResetTimer);

	GetWorld()->GetTimerManager().SetTimer(ResetTimer, [this, WidgetName] {
		for (ABaseStagePlayerController* PlayerController : PlayerControllers)
		{
			if(PlayerController)
				PlayerController->AddRemoveWidget(WidgetName);
		}
		}, 2.f, false);
}

void ABaseStageGameMode::ShowHideControllerWidget(FString const& WidgetName)
{
	GetWorld()->GetTimerManager().ClearTimer(ResetTimer);

	GetWorld()->GetTimerManager().SetTimer(ResetTimer, [this, WidgetName] {
		for (ABaseStagePlayerController* PlayerController : PlayerControllers)
		{
			if (PlayerController)
				PlayerController->ShowHideWidget(WidgetName);
		}
		}, 2.f, false);
}

void ABaseStageGameMode::SetUpTimerWidget(float const& Time)
{
	for (ABaseStagePlayerController* PlayerController : PlayerControllers)
	{
		if (PlayerController)
			PlayerController->SetUpTimerWidget(Time);
	}
}

ULevelSequencePlayer* ABaseStageGameMode::PlaySequence(int32 const& SequenceID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FSequenceData> SequenceData = GameInstance->GetDatabaseMap<FSequenceData>(E_ManagerType::E_SequenceDatabaseManager, SequenceID);
		if (SequenceData.IsValid())
		{
			ULevelSequence* LevelSequence = SequenceData.Pin()->SequenceClass.LoadSynchronous();
			if (LevelSequence)
			{
				ALevelSequenceActor* SequenceActor;
				ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), SequenceActor);

				if (SequencePlayer)
				{
					for (ABaseStagePlayerController* PlayerController : PlayerControllers)
					{
						if (PlayerController)
						{
							PlayerController->PlaySequence(SequencePlayer);
						}
					}

					return SequencePlayer;
				}
			}
		}
	}

	return nullptr;
}