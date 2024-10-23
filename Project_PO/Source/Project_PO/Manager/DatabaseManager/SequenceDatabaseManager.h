// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DatabaseManager.h"
#include "SequenceDatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API USequenceDatabaseManager : public UDatabaseManager
{
	GENERATED_BODY()
public:
	USequenceDatabaseManager();
	virtual ~USequenceDatabaseManager();

protected:
	virtual void GetMyData() override;
};
