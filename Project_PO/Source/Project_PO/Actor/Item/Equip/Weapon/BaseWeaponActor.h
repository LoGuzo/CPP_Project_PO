// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EquipItemActor.h"
#include "../../../../MyEnumClass.h"
#include "BaseWeaponActor.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_PO_API ABaseWeaponActor : public AEquipItemActor
{
	GENERATED_BODY()
	
public:
	ABaseWeaponActor();

protected:
	E_WeaponType WeaponType;

public:
	E_WeaponType GetWeaponType() { return WeaponType; }

	UFUNCTION()
	virtual void Fire() PURE_VIRTUAL(ABaseWeaponActor::Fire, ;);
};
