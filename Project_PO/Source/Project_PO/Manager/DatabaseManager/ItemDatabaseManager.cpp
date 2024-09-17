/// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDatabaseManager.h"

UItemDatabaseManager::UItemDatabaseManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("/Game/DataTable/DT_ItemData.DT_ItemData"));

	MyData = DATA.Object;
}

UItemDatabaseManager::~UItemDatabaseManager()
{
	if (MySharedData != nullptr)
		MySharedData.Reset();
}

TMap<int32, TSharedPtr<FTableRowBase>> UItemDatabaseManager::GetDataMap()
{
	const TArray<FName> row = MyData->GetRowNames();
	TMap<int32, TSharedPtr<FTableRowBase>> DataMap;

	for (int32 i = 0; i < row.Num(); i++)
	{
		const auto data = MyData->FindRow<FItemData>(row[i], row[i].ToString(), false);
		if (data)
		{
			MySharedData = MakeShared<FItemData>(*data);
			DataMap.Emplace(data->ItemID, MySharedData);
		}
		else
			MySharedData.Reset();
	}

	return DataMap;
}