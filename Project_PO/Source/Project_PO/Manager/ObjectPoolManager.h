// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../MyStructureAll.h"
#include "ObjectPoolManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UObjectPoolManager : public UObject
{
	GENERATED_BODY()
	
private:
	TArray<class AEnemyCharacter*> AvailableMonsters;
	TArray<class AEnemyCharacter*> InUseMonsters;

	TArray<class ABaseItemActor*> AvailableItems;
	TArray<class ABaseItemActor*> InUseItems;

public:
	class AEnemyCharacter* GetMonster(UWorld* World, E_MonsterType const& Type
		, FTransform const& Transform = FTransform()
		, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters()
	);
	void ReleaseMonster(class AEnemyCharacter* Monster);

	class ABaseItemActor* GetItem(UWorld* World, FSpawnItemType const& Type
		, FTransform const& Transform = FTransform()
		, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters()
	);
	void ReleaseItem(class ABaseItemActor* Item);
};
