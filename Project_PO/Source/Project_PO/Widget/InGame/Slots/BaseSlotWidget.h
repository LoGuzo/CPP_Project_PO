// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseInGameWidget.h"
#include "BaseSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBaseSlotWidget : public UBaseInGameWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class USizeBox* Box_Slot;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Slot;
};
