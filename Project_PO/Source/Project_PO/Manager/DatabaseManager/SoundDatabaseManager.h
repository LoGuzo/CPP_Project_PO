// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DatabaseManager.h"
#include "SoundDatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API USoundDatabaseManager : public UDatabaseManager
{
	GENERATED_BODY()
	
public:
	USoundDatabaseManager();
	virtual ~USoundDatabaseManager();

protected:
	virtual void GetMyData() override;
};
