// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDatabaseManager.h"
#include "EquipItemDatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UEquipItemDatabaseManager : public UItemDatabaseManager
{
	GENERATED_BODY()
	
public:
	UEquipItemDatabaseManager();
	virtual ~UEquipItemDatabaseManager();
};
