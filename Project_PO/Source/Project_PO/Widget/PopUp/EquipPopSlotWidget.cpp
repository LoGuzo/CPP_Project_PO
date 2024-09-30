// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPopSlotWidget.h"
#include "Components/Button.h"
#include "../../Component/InventoryComponent.h"

void UEquipPopSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Use && !Btn_Use->OnClicked.IsAlreadyBound(this, &UEquipPopSlotWidget::EquipItem))
		Btn_Use->OnClicked.AddDynamic(this, &UEquipPopSlotWidget::EquipItem);
}

void UEquipPopSlotWidget::EquipItem()
{
	if (InventoryComponent)
		InventoryComponent->ChangeEquip(Index, ItemID);
}