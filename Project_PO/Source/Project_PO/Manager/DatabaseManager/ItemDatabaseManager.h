// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DatabaseManager.h"
#include "ItemDatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UItemDatabaseManager : public UDatabaseManager
{
	GENERATED_BODY()
	
public:
	UItemDatabaseManager();
	virtual ~UItemDatabaseManager();

protected:
	virtual void GetMyData() override;
};
