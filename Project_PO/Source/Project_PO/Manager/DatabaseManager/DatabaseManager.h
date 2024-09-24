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
	
public:
	UDatabaseManager() {};
	virtual ~UDatabaseManager();

protected:
	UPROPERTY()
	UDataTable* MyData;

	TSharedPtr<FTableRowBase> MySharedData;


protected:
	virtual void GetMyData() PURE_VIRTUAL(UDatabaseManager::GetMyData, ;);

public:
	template<typename T>
	TMap<int32, TSharedPtr<FTableRowBase>>GetDataMap()
	{
		GetMyData();

		if(!MyData)
			return TMap<int32, TSharedPtr<FTableRowBase>>();

		const TArray<FName> row = MyData->GetRowNames();
		TMap<int32, TSharedPtr<FTableRowBase>> DataMap;

		for (int32 i = 0; i < row.Num(); i++)
		{
			const T* data = MyData->FindRow<T>(row[i], row[i].ToString(), false);
			if (data)
			{
				MySharedData = MakeShared<T>(*data);
				DataMap.Emplace(data->ID, MySharedData);
			}
			else
				MySharedData.Reset();
		}
		return DataMap;
	}
};

