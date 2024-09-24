// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DatabaseManager.h"
#include "ClassDatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UClassDatabaseManager : public UDatabaseManager
{
	GENERATED_BODY()
	
public:
	UClassDatabaseManager();
	virtual ~UClassDatabaseManager();

protected:
	virtual void GetMyData() override;
};
