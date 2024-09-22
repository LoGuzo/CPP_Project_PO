// Fill out your copyright notice in the Description page of Project Settings.


#include "DatabaseManager.h"

UDatabaseManager::~UDatabaseManager()
{
	if (MyData)
		MyData = nullptr;

	if (MySharedData.IsValid())
		MySharedData.Reset();
}
