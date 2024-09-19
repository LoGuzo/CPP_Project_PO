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

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

protected:
    virtual void BeginPlay() override;
};



