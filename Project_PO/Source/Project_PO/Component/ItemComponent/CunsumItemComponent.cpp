// Fill out your copyright notice in the Description page of Project Settings.


#include "CunsumItemComponent.h"
#include "../../Manager/BaseGameInstance.h"

UCunsumItemComponent::UCunsumItemComponent()
{

}

void UCunsumItemComponent::SetItem(int32 _ID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FCunsumItemData> ItemData = GameInstance->GetDatabaseMap<FCunsumItemData>(E_ManagerType::E_ItemDatabaseManager, _ID);
		if (ItemData.IsValid())
		{
			ID = ItemData.Pin()->ID;
			ItemName = ItemData.Pin()->ItemName;
			ItemDescription = ItemData.Pin()->ItemDescription;
			ItemImage = ItemData.Pin()->ItemImage;
			ItemStackSize = ItemData.Pin()->ItemStackSize;
			ItemType = ItemData.Pin()->ItemType;
			ItemMesh = ItemData.Pin()->ItemMesh;
			RestoreAmount = ItemData.Pin()->RestoreAmount;
			Duration = ItemData.Pin()->Duration;
			Cooltime = ItemData.Pin()->Cooltime;
		}
	}
}
