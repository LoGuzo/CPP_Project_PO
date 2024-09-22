// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../MyEnumClass.h"
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
	class AEnemyCharacter* GetMonster(UWorld* World, E_MonsterType Type
		, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator);
	void ReleaseMonster(class AEnemyCharacter* Monster);

	class ABaseItemActor* GetItem(UWorld* World, E_ItemType Type
		, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator
		, E_EquipType EquipType = E_EquipType::E_None, E_WeaponType WeaponType = E_WeaponType::E_None);
	void ReleaseItem(class ABaseItemActor* Item);
};
