// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUserWidget.h"

UBaseUserWidget::UBaseUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Type(E_WidgetType::E_None)
{

}

void UBaseUserWidget::InitializeWidget()
{
}

void UBaseUserWidget::SetShowHidden()
{
	if (GetVisibility() == ESlateVisibility::Hidden)
		SetVisibility(ESlateVisibility::Visible);
	else
		SetVisibility(ESlateVisibility::Hidden);
}

void UBaseUserWidget::SetAddRemove()
{
	if (IsInViewport())
		RemoveFromParent();
	else
		AddToViewport();
}
