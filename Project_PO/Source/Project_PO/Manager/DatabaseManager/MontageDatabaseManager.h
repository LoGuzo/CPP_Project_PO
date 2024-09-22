// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DatabaseManager.h"
#include "MontageDatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UMontageDatabaseManager : public UDatabaseManager
{
	GENERATED_BODY()
	
public:
	UMontageDatabaseManager();
	virtual ~UMontageDatabaseManager();

protected:
	virtual void GetMyData() override;
};
