// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemComponent.h"
#include "CunsumItemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UCunsumItemComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
    UCunsumItemComponent();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable", Meta = (AllowPrivateAccess = true))
    float RestoreAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable", Meta = (AllowPrivateAccess = true))
    float Duration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable", Meta = (AllowPrivateAccess = true))
    float Cooltime;

public:
    virtual void SetItem(int32 _ID) override;

    float GetRestoreAmount() { return RestoreAmount; }
    float GetDuration() { return Duration; }
    float GetCooltime() { return Cooltime; }
};
