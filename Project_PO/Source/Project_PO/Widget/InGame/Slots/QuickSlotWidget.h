// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSlotWidget.h"
#include "QuickSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UQuickSlotWidget : public UBaseSlotWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Key;

public:
	void SetUpWidget(int32 const& _ID);
	void SetTextKey(FString const& Key);
};
