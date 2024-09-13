// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractionWidget.h"

UBaseInteractionWidget::UBaseInteractionWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Type = E_WidgetType::E_Interaction;
}
