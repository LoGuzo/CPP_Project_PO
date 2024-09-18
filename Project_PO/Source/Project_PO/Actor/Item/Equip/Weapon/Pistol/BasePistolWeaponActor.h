// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseWeaponActor.h"
#include "BasePistolWeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABasePistolWeaponActor : public ABaseWeaponActor
{
	GENERATED_BODY()
	
public:
	ABasePistolWeaponActor();

public:
	virtual void Fire() override;
};
