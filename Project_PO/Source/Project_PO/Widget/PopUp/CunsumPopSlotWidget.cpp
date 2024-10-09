// Fill out your copyright notice in the Description page of Project Settings.


#include "CunsumPopSlotWidget.h"
#include "Components/Button.h"
#include "../../Component/InventoryComponent.h"

void UCunsumPopSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Use && !Btn_Use->OnClicked.IsAlreadyBound(this, &UCunsumPopSlotWidget::UseItem))
		Btn_Use->OnClicked.AddDynamic(this, &UCunsumPopSlotWidget::UseItem);
	if (Type.EquipType == E_EquipType::E_Registerable)
	{
		if (Btn_Register && !Btn_Register->OnClicked.IsAlreadyBound(this, &UCunsumPopSlotWidget::RegisterItem))
			Btn_Register->OnClicked.AddDynamic(this, &UCunsumPopSlotWidget::RegisterItem);
	}
	else
	{
		if (Btn_Register)
			Btn_Register->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCunsumPopSlotWidget::UseItem()
{
	if (InventoryComponent)
		InventoryComponent->UseItem(Index, Type);

	RemoveFromParent();
}

void UCunsumPopSlotWidget::RegisterItem()
{
	if (InventoryComponent)
		InventoryComponent->RegisterQuickSlot(Index);

	RemoveFromParent();
}
