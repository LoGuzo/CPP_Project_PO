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
	
private:
	TMap<E_ManagerType, TMap<int32, TSharedPtr<FTableRowBase>>> DatabaseMap;

public:
	template<typename T>
	TSharedPtr<T> GetDatabaseMap(E_ManagerType Type, int32 ID)
	{
		return StaticCastSharedPtr<T>(*DatabaseMap.Find(Type)->Find(ID));
	}
};



