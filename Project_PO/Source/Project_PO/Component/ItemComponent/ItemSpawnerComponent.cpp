// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawnerComponent.h"
#include "../../Actor/Item/BaseItemActor.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/ObjectPoolManager.h"

void UItemSpawnerComponent::AddSpawnItemIDs(TArray<int32> const& ItemIDs)
{
	for (int32 const& ItemID : ItemIDs)
		SpawnItemIDs.Emplace(ItemID);
}

void UItemSpawnerComponent::DropItems(FVector const& Location)
{
	if (SpawnItemIDs.Num() != 0)
	{
		for (int32 const& ItemID : SpawnItemIDs)
			SpawnItems(MyUtils::RandomVector(Location, 40.f), ItemID);
	}
}

void UItemSpawnerComponent::SpawnItems(FVector const& Location, int32 const& ItemID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UObjectPoolManager* ObjectPoolManager = GameInstance->GetManager<UObjectPoolManager>(E_ManagerType::E_ObjectPoolManager);
		if (ObjectPoolManager)
		{
			FSpawnItemType Type = FSpawnItemType(E_ItemType::E_Drop);

			ABaseItemActor* DropItem = ObjectPoolManager->GetItem(GetWorld(), Type);
			if (DropItem)
			{
				DropItem->SetItem(ItemID);
				DropItem->SetActorLocation(Location);
			}
		}
	}
}