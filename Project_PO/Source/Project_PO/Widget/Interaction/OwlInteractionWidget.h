// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractionWidget.h"
#include "OwlInteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UOwlInteractionWidget : public UBaseInteractionWidget
{
	GENERATED_BODY()
	
public:
	void SetTextContent(const FString& Text);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Key;
};
