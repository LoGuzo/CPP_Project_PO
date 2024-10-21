// Fill out your copyright notice in the Description page of Project Settings.


#include "CunsumQuickSlotWidget.h"
#include "Components/TextBlock.h"
#include "../../../Component/QuickSlotComponent/PotionQuickSlotComponent.h"

void UCunsumQuickSlotWidget::SetUpSlot()
{
	if (PotionQuickSlotComponent)
	{
		Slot = PotionQuickSlotComponent->GetSlot();

		SetUpWidget(Slot.ItemID);
		SetText();
	}
}

void UCunsumQuickSlotWidget::BindText(UPotionQuickSlotComponent* _PotionQuickSlotComponent)
{
	if (_PotionQuickSlotComponent)
	{
		PotionQuickSlotComponent = _PotionQuickSlotComponent;
		PotionQuickSlotComponent->OnQuickSlotUpdated.AddUObject(this, &UCunsumQuickSlotWidget::SetText);
	}

}

void UCunsumQuickSlotWidget::SetText()
{
	if (PotionQuickSlotComponent)
	{
		Slot = PotionQuickSlotComponent->GetSlot();
		if (Txt_Slot)
			Txt_Slot->SetText(FText::FromString(FString::FromInt(Slot.Amount)));
	}
}