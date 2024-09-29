// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/WrapBox.h"
#include "../Slots/InventorySlotWidget.h"
#include "../../../Component/InventoryComponent.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("/Game/ThirdPerson/Blueprints/Widget/InGame/Slots/WBP_InventorySlot.WBP_InventorySlot_C"));
	if (UW.Succeeded())
		SlotWidget = UW.Class;
}

void UInventoryWidget::UpdateSlots(const TArray<FSlot>& Slots)
{
	int32 index = 0;
	for (const FSlot& slot : Slots)
	{
		UInventorySlotWidget* SlotsWidget = CreateWidget<UInventorySlotWidget>(this, SlotWidget);
		if (SlotsWidget)
		{
			SlotsWidget->SetItemID(slot.ItemID);
			SlotsWidget->SetAmount(slot.Amount);
			SlotsWidget->SetType(slot.Type);
			SlotsWidget->SetConIndex(index);
			//SlotsWidget->OnCloseItemPop.AddUObject(this, &UW_Inventory::ClosePop);
		}
		Wrap_Item->AddChild(SlotsWidget);
		index++;
	}
}

void UInventoryWidget::UpdateInventory(UInventoryComponent* _InventoryComponent)
{
	InventoryComponent = _InventoryComponent;
	Wrap_Item->ClearChildren();
	UpdateSlots(InventoryComponent->GetSlots());
	InventoryComponent->OnInventoryUpdated.AddUObject(this, &UInventoryWidget::UpdateInventoryDrop);
}

void UInventoryWidget::UpdateInventoryDrop()
{
	Wrap_Item->ClearChildren();
	UpdateSlots(InventoryComponent->GetSlots());
}
