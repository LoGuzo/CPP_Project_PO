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
    float AttackPower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", Meta = (AllowPrivateAccess = true))
    float DefensePower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    TSubclassOf<UAnimInstance> WeaponAnimInstance;

public:
    virtual void SetItem(int32 _ID) override;
    float GetAttackPower() { return AttackPower; }
    float GetDefensePower() { return DefensePower; }
    TSubclassOf<UAnimInstance> GetWeaponAnimInstance() { return WeaponAnimInstance; }
};
