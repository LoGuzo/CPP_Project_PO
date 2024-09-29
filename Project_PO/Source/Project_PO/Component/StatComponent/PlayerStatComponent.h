// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatComponent.h"
#include "PlayerStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnExpChanged);

UCLASS()
class PROJECT_PO_API UPlayerStatComponent : public UStatComponent
{
	GENERATED_BODY()

public:
    UPlayerStatComponent();

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat", Meta = (AllowPrivateAccess = true))
    E_ClassType ClassType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat", Meta = (AllowPrivateAccess = true))
    int32 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat", Meta = (AllowPrivateAccess = true))
    int32 MaxLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat", Meta = (AllowPrivateAccess = true))
    float Speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat", Meta = (AllowPrivateAccess = true))
    float AttackSpeed;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat", Meta = (AllowPrivateAccess = true))
    float Exp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStat", Meta = (AllowPrivateAccess = true))
    float MaxExp;

public:
    virtual void SetStat(int32 const& _ID) override;
    void SetLevel(int32 const& _Level);

    void TakedExp(float const& TakedExp);
    void SetExp(float const& _Exp);

    float GetSpeed() { return Speed; }
    float GetAttackSpeed() { return AttackSpeed; }
    float GetExpRatio() { return Exp / MaxExp; }

    FOnExpChanged OnExpChanged;
};
