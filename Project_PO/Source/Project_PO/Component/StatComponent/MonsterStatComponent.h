// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatComponent.h"
#include "../../MyEnumClass.h"
#include "MonsterStatComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UMonsterStatComponent : public UStatComponent
{
	GENERATED_BODY()
	
public:
    UMonsterStatComponent();

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat", Meta = (AllowPrivateAccess = true))
    FName MonsterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat", Meta = (AllowPrivateAccess = true))
    float RewardEXP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat", Meta = (AllowPrivateAccess = true))
    float AttackRange;

public:
    virtual void SetStat(int32 const& _ID) override;

    FName GetMonsterName() { return MonsterName; }
    void SetMonsterName(FName const& _MonsterName) { MonsterName = _MonsterName; }

    float GetRewardExp() { return RewardEXP; }

    float GetAttackRange() { return AttackRange; }
};
