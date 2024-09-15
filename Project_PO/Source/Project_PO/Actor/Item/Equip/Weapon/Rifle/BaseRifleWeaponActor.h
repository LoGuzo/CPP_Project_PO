// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseWeaponActor.h"
#include "BaseRifleWeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABaseRifleWeaponActor : public ABaseWeaponActor
{
	GENERATED_BODY()
	
public:
	ABaseRifleWeaponActor();

public:
	virtual void Fire() override;
};
