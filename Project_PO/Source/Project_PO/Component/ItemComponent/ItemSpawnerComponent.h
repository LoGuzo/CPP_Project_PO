// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseActorComponent.h"
#include "../../MyUtils.h"
#include "ItemSpawnerComponent.generated.h"

using namespace MyUtils;

UCLASS()
class PROJECT_PO_API UItemSpawnerComponent : public UBaseActorComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "IDs", meta = (AllowPrivateAccess = "true"))
	TArray<int32> SpawnItemIDs;

public:
	UFUNCTION(BlueprintCallable)
	void AddSpawnItemIDs(TArray<int32> const& ItemIDs);
	void DropItems(FVector const& Location);
	void SpawnItems(FVector const& Location, int32 const& ItemID);
};