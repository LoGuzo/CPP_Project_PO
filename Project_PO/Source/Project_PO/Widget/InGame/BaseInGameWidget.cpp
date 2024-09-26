// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInGameWidget.h"

UBaseInGameWidget::UBaseInGameWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Type = E_WidgetType::E_InGame;
}
