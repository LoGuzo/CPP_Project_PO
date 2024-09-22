// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../MyEnumClass.h"
#include "FactoryManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UFactoryManager : public UObject
{
	GENERATED_BODY()
	
private:
	class ABaseItemActor* EquipFactory(UWorld* World, E_EquipType EquipType
		, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator
		, E_WeaponType WeaponType = E_WeaponType::E_None);
	class ABaseItemActor* WeaponFactory(UWorld* World, E_WeaponType WeaponType
		, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator);

public:
	class AEnemyCharacter* MonsterFactory(UWorld* World, E_MonsterType Type
		, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator);
	class ABaseItemActor* ItemFactory(UWorld* World, E_ItemType Type
		, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator
		, E_EquipType EquipType = E_EquipType::E_None, E_WeaponType WeaponType = E_WeaponType::E_None);
};
