// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseActorComponent.h"
#include "CombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UCombatComponent : public UBaseActorComponent
{
	GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, Category = "Attack")
    float Damage;

    UPROPERTY(VisibleAnywhere, Category = "Attack")
    float AttackRange;

    UPROPERTY(VisibleAnywhere, Category = "Attack")
    float Cooldown;

public:
	virtual void UseSkill() {};
};
