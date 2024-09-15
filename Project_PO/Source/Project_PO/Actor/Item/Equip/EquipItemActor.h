// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseItemActor.h"
#include "EquipItemActor.generated.h"


UENUM(BlueprintType)
enum class E_EquipType : uint8
{
	E_Weapon UMETA(DisplayName = "Weapon"),
	E_Hat UMETA(DisplayName = "Hat"),
	E_Shoes UMETA(DisplayName = "Shoes"),
	E_Chest UMETA(DisplayName = "Chest"),
	E_Gloves UMETA(DisplayName = "Gloves"),
	E_None UMETA(DisplayName = "None"),
};

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AEquipItemActor : public ABaseItemActor
{
	GENERATED_BODY()
	
public:
	AEquipItemActor();

protected:
	E_EquipType EquipType;

public:
	E_EquipType GetEquipType() { return EquipType; }
};
