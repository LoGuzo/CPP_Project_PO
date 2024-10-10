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

private:
	FTimerHandle ResetTimer;

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer);

protected:
	void StartQuest();
};



