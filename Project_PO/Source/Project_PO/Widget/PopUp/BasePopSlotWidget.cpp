// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePopSlotWidget.h"
#include "Components/Button.h"
#include "../../Component/InventoryComponent.h"

void UBasePopSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Drop && !Btn_Drop->OnClicked.IsAlreadyBound(this, &UBasePopSlotWidget::DropItem))
		Btn_Drop->OnClicked.AddDynamic(this, &UBasePopSlotWidget::DropItem);
}

void UBasePopSlotWidget::DropItem()
{
	if (InventoryComponent)
		InventoryComponent->DropItem(Index);
}