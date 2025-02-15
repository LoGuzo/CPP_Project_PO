// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseActorComponent.h"
#include "../../MyEnumClass.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);
DECLARE_MULTICAST_DELEGATE(FOnMpChanged);


UCLASS()
class PROJECT_PO_API UStatComponent : public UBaseActorComponent
{
	GENERATED_BODY()
	
public:
    UStatComponent();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat", Meta = (AllowPrivateAccess = true))
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float Attack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float AttackSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float Armor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float Hp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float MaxHp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float Mp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess = true))
    float MaxMp;

public:
    virtual void SetStat(int32 const& _ID) {};
    void ResetStat();

    float GetHp() { return Hp; }
    void SetHp(float const& _Hp);
    virtual void TakeDamage(float const& TakedDamage);
    void HealHp(float const& HealedHp);

    float GetMaxHp() { return MaxHp; }

    float GetMp() { return Mp; }
    void SetMp(float const& _Mp);
    void UseMana(float const& UsedMana);
    void HealMp(float const& HealedMp);

    float GetAttack() { return Attack; }
    float GetAttackSpeed() { return AttackSpeed; }
    float GetArmor() { return Armor; }

    float GetHpRatio() { return Hp / MaxHp; }
    float GetMpRatio() { return Mp / MaxMp; }

    FOnHpChanged OnHpChanged;
    FOnMpChanged OnMpChanged;
};
