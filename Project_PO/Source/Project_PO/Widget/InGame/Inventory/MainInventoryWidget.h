// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseInGameWidget.h"
#include "MainInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UMainInventoryWidget : public UBaseInGameWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	class UInventoryWidget* WBP_Inventory;
};
