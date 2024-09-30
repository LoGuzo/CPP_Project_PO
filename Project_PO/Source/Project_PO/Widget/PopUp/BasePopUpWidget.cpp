// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePopUpWidget.h"

UBasePopUpWidget::UBasePopUpWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Type = E_WidgetType::E_PopUp;
}
