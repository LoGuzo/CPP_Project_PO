// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemComponent.h"
#include "../../Manager/BaseGameInstance.h"

// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UItemComponent::SetItem(int32 _ID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FItemData> ItemData = GameInstance->GetDatabaseMap<FItemData>(E_ManagerType::E_ItemDatabaseManager, _ID);
		if (ItemData.IsValid())
		{
			ID = ItemData.Pin()->ID;
			ItemName = ItemData.Pin()->ItemName;
			ItemDescription = ItemData.Pin()->ItemDescription;
			ItemImage = ItemData.Pin()->ItemImage;
			ItemStackSize = ItemData.Pin()->ItemStackSize;
			ItemType = ItemData.Pin()->ItemType;
			ItemMesh = ItemData.Pin()->ItemMesh;
		}
	}
}

void UItemComponent::ResetItem()
{
	ID = -1;
	ItemName = FText();
	ItemDescription = FText();
	ItemImage = nullptr;
	ItemStackSize = 0;
	ItemType = FSpawnItemType();
	ItemMesh = nullptr;
}

