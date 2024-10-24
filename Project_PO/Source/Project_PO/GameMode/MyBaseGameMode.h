// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../MyStructureAll.h"
#include "MyBaseGameMode.generated.h"

UCLASS(minimalapi)
class AMyBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyBaseGameMode();

protected:
	virtual void BeginPlay() override;

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer);

private:
	FTimerHandle ResetTimer;

	bool bIsHavingFirstPlayer;

protected:
	UPROPERTY()
	TArray<class ABasePlayerController*> PlayerControllers;

	int32 FirstQuestID;

private:
	void InitPlayerController(APlayerController* NewPlayer);

protected:
	void StartQuest();
	void BindingReward();
	void GrantReward(int32 QuestID);

public:
	TArray<class ABasePlayerController*> GetPlayerControllers() { return PlayerControllers; }

	void AddRemoveControllerWidget(FString const& WidgetName);
	void ShowHideControllerWidget(FString const& WidgetName);
	void SetUpTimerWidget(float const& Time);

	class ULevelSequencePlayer* PlaySequence(int32 const& SequenceID);
};



