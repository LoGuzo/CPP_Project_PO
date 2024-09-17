// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseWeaponActor.h"
#include "BaseShotgunWeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABaseShotgunWeaponActor : public ABaseWeaponActor
{
	GENERATED_BODY()

public:
	ABaseShotgunWeaponActor();

public:
	virtual void Fire() override;
};
