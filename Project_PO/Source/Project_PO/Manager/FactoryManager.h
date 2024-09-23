// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../MyStructureAll.h"
#include "FactoryManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UFactoryManager : public UObject
{
	GENERATED_BODY()
	
private:
	class ABaseItemActor* EquipFactory(UWorld* World, FSpawnItemType const& Type
		, FTransform const& Transform
		, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters()
	);

	class ABaseItemActor* WeaponFactory(UWorld* World, FSpawnItemType const& Type
		, FTransform const& Transform
		, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters()
	);

public:
	class AEnemyCharacter* MonsterFactory(UWorld* World, E_MonsterType const& Type
		, FTransform const& Transform
		, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters()
	);

	class ABaseItemActor* ItemFactory(UWorld* World, FSpawnItemType const& Type
		, FTransform const& Transform
		, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters()
	);
};
