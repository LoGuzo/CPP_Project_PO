// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameMode.h"
#include "../MyStructureAll.h"
#include "BaseStageGameMode.generated.h"

UCLASS(minimalapi)
class ABaseStageGameMode : public ABaseGameMode
{
	GENERATED_BODY()

public:
	ABaseStageGameMode();

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
	TArray<class ABaseStagePlayerController*> PlayerControllers;

	int32 FirstQuestID;

private:
	void InitPlayerController(APlayerController* NewPlayer);

protected:
	void StartQuest();
	void BindingReward();
	void GrantReward(int32 QuestID);

public:
	TArray<class ABaseStagePlayerController*> GetPlayerControllers() { return PlayerControllers; }

	void AddRemoveControllerWidget(FString const& WidgetName);
	void ShowHideControllerWidget(FString const& WidgetName);
	void SetUpTimerWidget(float const& Time);

	class ULevelSequencePlayer* PlaySequence(int32 const& SequenceID);
	void PlayBackGound(FString const& SoundName);
};



