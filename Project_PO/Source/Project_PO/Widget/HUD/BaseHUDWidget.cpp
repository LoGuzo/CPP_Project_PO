// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUDWidget.h"

UBaseHUDWidget::UBaseHUDWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Type = E_WidgetType::E_HUD;
}