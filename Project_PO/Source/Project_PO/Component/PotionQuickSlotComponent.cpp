// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionQuickSlotComponent.h"
#include "InventoryComponent.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/WidgetManager.h"
#include "../Widget/HUD/MyHUDWidget.h"
#include "../Widget/InGame/Slots/CunsumQuickSlotWidget.h"

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
	if (InventoryComponent)
	{
		if (Slot.Amount > 0)
		{
			InventoryComponent->UseItem(SlotIndex, E_ItemType::E_Cunsumable);
			UpdateQuickSlotAmount();
		}
		else
		{
			Slot = FSlot();
		}
	}
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
		if(Slot.ItemID != -1)
			Slot.Amount = InventoryComponent->CheckFullItemAmount(Slot.ItemID);
	}
}
