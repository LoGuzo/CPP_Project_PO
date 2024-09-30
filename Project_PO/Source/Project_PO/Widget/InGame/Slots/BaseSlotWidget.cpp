// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSlotWidget.h"
#include "Components/SizeBox.h"

void UBaseSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (Box_Slot)
		Box_Slot->SetVisibility(ESlateVisibility::Hidden);
}
