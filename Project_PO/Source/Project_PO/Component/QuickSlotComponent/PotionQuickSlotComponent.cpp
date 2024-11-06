// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionQuickSlotComponent.h"
#include "../InventoryComponent.h"
#include "../../Actor/Item/BaseItemActor.h"
#include "../../Character/Player/PlayerCharacter.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/ObjectPoolManager.h"
#include "../../Manager/WidgetManager.h"
#include "../../Widget/HUD/MyHUDWidget.h"
#include "../../Widget/InGame/Slots/CunsumQuickSlotWidget.h"

UPotionQuickSlotComponent::UPotionQuickSlotComponent()
{
}

void UPotionQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupQuickSlotWidget();
}

void UPotionQuickSlotComponent::RegisterQuickSlot(int32 const& _SlotIndex, UBaseActorComponent* ActorComponent)
{
	if (ActorComponent)
	{
		InventoryComponent = Cast<UInventoryComponent>(ActorComponent);
		if (InventoryComponent)
		{
			SlotIndex = _SlotIndex;
			Slot = InventoryComponent->GetSlot(SlotIndex, E_ItemType::E_Cunsumable);
			UpdateQuickSlotAmount();
			UpdateQuickSlotWidget();
		}
	}
}

void UPotionQuickSlotComponent::UseSlot()
{
	if (Slot.ItemID == -1)
		return;

	if (InventoryComponent)
	{
		if (Slot.Amount > 0)
		{
			InventoryComponent->UseItem(SlotIndex, E_ItemType::E_Cunsumable);
			UpdateQuickSlotAmount();
		}

		if(OwnPlayer)
			OwnPlayer->UsePotion();

		SetUpQuickItem();

		if (Slot.Amount < 1)
		{
			SlotIndex = -1;
			Slot = FSlot();
		}

		UpdateQuickSlotWidget();
	}
}

FSlot UPotionQuickSlotComponent::GetSlot()
{
	UpdateQuickSlotAmount();

	return Slot;
}

void UPotionQuickSlotComponent::SetupQuickSlotWidget()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UMyHUDWidget* MyHUD = WidgetManager->GetWidget<UMyHUDWidget>(TEXT("HUD"));
			if (MyHUD)
				MyHUD->SetUpCunsumQuickSlot(this);
		}
	}

}

void UPotionQuickSlotComponent::UpdateQuickSlotWidget()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UMyHUDWidget* MyHUD = WidgetManager->GetWidget<UMyHUDWidget>(TEXT("HUD"));
			if (MyHUD)
			{
				UCunsumQuickSlotWidget* CunsumQuickSlotWidget = MyHUD->GetCunsumQuickSlot();
				if (CunsumQuickSlotWidget)
				{
					CunsumQuickSlotWidget->SetUpSlot();
				}
			}
		}
	}
}

void UPotionQuickSlotComponent::UpdateQuickSlotAmount()
{
	if (InventoryComponent)
	{
		if (Slot.ItemID != -1)
		{
			FMinResult Result = InventoryComponent->CheckFullItemAmount(Slot.ItemID);

			SlotIndex = Result.Index;
			Slot.Amount = Result.Amount;
		}
	}
}

void UPotionQuickSlotComponent::SetUpQuickItem()
{
	if (CurItem)
	{
		CurItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurItem->ResetItem();
		CurItem = nullptr;
	}
	else
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			UObjectPoolManager* ObjectPoolManager = GameInstance->GetManager<UObjectPoolManager>(E_ManagerType::E_ObjectPoolManager);

			if (!ObjectPoolManager)
				return;

			FName SocketName = FName(TEXT("potion_socket"));

			FSpawnItemType Type = FSpawnItemType(E_ItemType::E_Cunsumable);

			CurItem = ObjectPoolManager->GetItem(GetWorld(), Type, FTransform());
			if (CurItem)
			{
				CurItem->SetItem(Slot.ItemID);
				CurItem->SetOwner(OwnPlayer);
				CurItem->AttachToComponent(OwnPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
			}
		}
	}
}
