// Fill out your copyright notice in the Description page of Project Settings.


#include "DatabaseManager.h"


UDataTable* UDatabaseManager::MyData = nullptr;
TSharedPtr<FTableRowBase> UDatabaseManager::MySharedData = nullptr;

UDatabaseManager::~UDatabaseManager()
{
	if (MyData)
		MyData = nullptr;

	if (MySharedData.IsValid())
		MySharedData.Reset();
}
