// Fill out your copyright notice in the Description page of Project Settings.


#include "OwlInteractionWidget.h"
#include "Components/TextBlock.h"

void UOwlInteractionWidget::SetTextContent(const FString& Text)
{
	if (Txt_Key)
		Txt_Key->SetText(FText::FromString(Text));
}