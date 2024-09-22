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
	class ABaseItemActor* EquipFactory(E_EquipType EquipType, E_WeaponType WeaponType = E_WeaponType::E_None);
	class ABaseItemActor* WeaponFactory(E_WeaponType WeaponType);

public:
	class AEnemyCharacter* MonsterFactory(E_MonsterType Type);
	class ABaseItemActor* ItemFactory(E_ItemType Type, E_EquipType EquipType = E_EquipType::E_None, E_WeaponType WeaponType = E_WeaponType::E_None);
};
