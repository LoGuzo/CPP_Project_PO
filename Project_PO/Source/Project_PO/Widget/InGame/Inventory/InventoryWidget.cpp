// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/Button.h"
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

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Equip && !Btn_Equip->OnClicked.IsAlreadyBound(this, &UInventoryWidget::EquipInven))
		Btn_Equip->OnClicked.AddDynamic(this, &UInventoryWidget::EquipInven);
	if (Btn_Cunsum && !Btn_Cunsum->OnClicked.IsAlreadyBound(this, &UInventoryWidget::CunsumInven))
		Btn_Cunsum->OnClicked.AddDynamic(this, &UInventoryWidget::CunsumInven);
	if (Btn_Etc && !Btn_Etc->OnClicked.IsAlreadyBound(this, &UInventoryWidget::EtcInven))
		Btn_Etc->OnClicked.AddDynamic(this, &UInventoryWidget::EtcInven);
}

void UInventoryWidget::UpdateSlots(const TArray<FSlot>& Slots)
{
	int32 index = 0;
	Wrap_Item->ClearChildren();

	for (const FSlot& slot : Slots)
	{
		UInventorySlotWidget* SlotsWidget = CreateWidget<UInventorySlotWidget>(this, SlotWidget);
		if (SlotsWidget)
		{
			SlotsWidget->SetItemID(slot.ItemID);
			SlotsWidget->SetAmount(slot.Amount);
			SlotsWidget->SetType(slot.Type);
			SlotsWidget->SetConIndex(index);
			SlotsWidget->SetInvetoryComponent(InventoryComponent);
			//SlotsWidget->OnCloseItemPop.AddUObject(this, &UW_Inventory::ClosePop);
		}
		Wrap_Item->AddChild(SlotsWidget);
		index++;
	}
}

void UInventoryWidget::EquipInven()
{
	InventoryComponent->SetItemType(E_ItemType::E_Equip);
	InventoryComponent->OnInventoryUpdated.Broadcast();
}

void UInventoryWidget::CunsumInven()
{
	InventoryComponent->SetItemType(E_ItemType::E_Cunsumable);
	InventoryComponent->OnInventoryUpdated.Broadcast();
}

void UInventoryWidget::EtcInven()
{
	InventoryComponent->SetItemType(E_ItemType::E_Etc);
	InventoryComponent->OnInventoryUpdated.Broadcast();
}

void UInventoryWidget::UpdateInventory(UInventoryComponent* _InventoryComponent)
{
	InventoryComponent = _InventoryComponent;
	UpdateSlots(InventoryComponent->GetSlots());
	InventoryComponent->OnInventoryUpdated.AddUObject(this, &UInventoryWidget::UpdateInventoryDrop);
}

void UInventoryWidget::UpdateInventoryDrop()
{
	Wrap_Item->ClearChildren();
	UpdateSlots(InventoryComponent->GetSlots());
}
