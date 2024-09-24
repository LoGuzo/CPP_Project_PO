// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActorComponent.h"
#include "../MyEnumClass.h"
#include "StatComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UStatComponent : public UBaseActorComponent
{
	GENERATED_BODY()
	
public:
    UStatComponent();

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    int32 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    int32 MaxLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    int32 ClassID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    E_ClassType ClassType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float Attack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float Armor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float Speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float AttackSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float Hp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float MaxHp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float Mp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float MaxMp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float Exp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float MaxExp;

public:
    void SetStat(int32 const& _ClassID);
    void SetLevel(int32 const& _Level);

    void TakeDamage(float const& TakedDamage);
    void HealHp(float const& HealedHp);

    void UseMana(float const& UsedMana);
    void HealMp(float const& HealedMp);

    void SetExp(float const& TakedExp);

    float GetAttack() { return Attack; }
    float GetArmor() { return Armor; }
    float GetSpeed() { return Speed; }
    float GetAttackSpeed() { return AttackSpeed; }

};
