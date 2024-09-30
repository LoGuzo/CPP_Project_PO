// Fill out your copyright notice in the Description page of Project Settings.


#include "CunsumQuickSlotWidget.h"
#include "Components/TextBlock.h"


void UCunsumQuickSlotWidget::SetText(int32 const& Amount)
{
	if (Txt_Slot)
		Txt_Slot->SetText(FText::FromString(FString::FromInt(Amount)));
}
