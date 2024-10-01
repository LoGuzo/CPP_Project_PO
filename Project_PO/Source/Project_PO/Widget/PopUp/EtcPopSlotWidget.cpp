// Fill out your copyright notice in the Description page of Project Settings.


#include "EtcPopSlotWidget.h"
#include "Components/Button.h"
#include "../../Component/InventoryComponent.h"

void UEtcPopSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Type.EquipType == E_EquipType::E_Installable)
	{
		if (Btn_Use && !Btn_Use->OnClicked.IsAlreadyBound(this, &UEtcPopSlotWidget::UseItem))
			Btn_Use->OnClicked.AddDynamic(this, &UEtcPopSlotWidget::UseItem);
	}
	else
	{
		if (Btn_Use)
			Btn_Use->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UEtcPopSlotWidget::UseItem()
{
	if (InventoryComponent)
		InventoryComponent->UseItem(Index);

	RemoveFromParent();
}
