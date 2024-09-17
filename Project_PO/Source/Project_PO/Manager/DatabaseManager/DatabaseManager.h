// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../MyStructureAll.h"
#include "DatabaseManager.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_PO_API UDatabaseManager : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	class UDataTable* MyData;

	TSharedPtr<FTableRowBase> MySharedData;

public:
	UDatabaseManager() {};
	virtual ~UDatabaseManager() {};

	virtual TMap<int32, TSharedPtr<FTableRowBase>> GetDataMap() PURE_VIRTUAL(UDatabaseManager::GetDataMap(), return TMap<int32, TSharedPtr<FTableRowBase>>(););
};
