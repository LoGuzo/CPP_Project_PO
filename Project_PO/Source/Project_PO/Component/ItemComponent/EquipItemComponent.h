// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemComponent.h"
#include "EquipItemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UEquipItemComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
    UEquipItemComponent();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", Meta = (AllowPrivateAccess = true))
    E_EquipType EquipType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", Meta = (AllowPrivateAccess = true))
    E_WeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", Meta = (AllowPrivateAccess = true))
    float AttackPower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", Meta = (AllowPrivateAccess = true))
    float DefensePower;

public:
    virtual void SetItem(int32 _ItemID) override;

    E_EquipType GetEquipType() { return EquipType; }
    E_WeaponType GetWeaponType() { return WeaponType; }
    float GetAttackPower() { return AttackPower; }
    float GetDefensePower() { return DefensePower; }
};
