// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../MyStructureAll.h"
#include "../MyUtils.h"
#include "ObjectPoolManager.generated.h"

using namespace MyUtils;

UCLASS()
class PROJECT_PO_API UObjectPoolManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TArray<class AEnemyCharacter*> AvailableMonsters;
	UPROPERTY()
	TArray<class AEnemyCharacter*> InUseMonsters;

	UPROPERTY()
	TArray<class ABaseItemActor*> AvailableItems;
	UPROPERTY()
	TArray<class ABaseItemActor*> InUseItems;

	UPROPERTY()
	TArray<class UDamagePopUpWidget*> AvailableDamageWidgets;
	UPROPERTY()
	TArray<class UDamagePopUpWidget*> InUseDamageWidgets;

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

	class UDamagePopUpWidget* GetWidget(UWorld* World, E_DamageType const& Type
		, TSubclassOf<class UDamagePopUpWidget> WidgetClass
		, FVector2D const& Loaction, int32 const& Damage);
	void ReleaseWidget(class UDamagePopUpWidget* Widget);
};
