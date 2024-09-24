// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActorComponent.h"
#include "../MyEnumClass.h"
#include "MonsterStatComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UMonsterStatComponent : public UBaseActorComponent
{
	GENERATED_BODY()
	
public:
    UMonsterStatComponent();

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat", Meta = (AllowPrivateAccess = true))
    FName MonsterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat", Meta = (AllowPrivateAccess = true))
    float Attack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat", Meta = (AllowPrivateAccess = true))
    float Armor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat", Meta = (AllowPrivateAccess = true))
    float Hp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat", Meta = (AllowPrivateAccess = true))
    float MaxHp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat", Meta = (AllowPrivateAccess = true))
    float Mp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat", Meta = (AllowPrivateAccess = true))
    float MaxMp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat", Meta = (AllowPrivateAccess = true))
    float RewardEXP;

public:
    void SetStat(int32 MonsterID);

    void TakeDamage(float const& TakedDamage);
    void HealHp(float const& HealedHp);

    void UseMana(float const& UsedMana);
    void HealMp(float const& HealedMp);

    float GetAttack() { return Attack; }
    float GetArmor() { return Armor; }
};
