// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuickSlotWidget.h"
#include "../../../MyStructureAll.h"
#include "CunsumQuickSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UCunsumQuickSlotWidget : public UQuickSlotWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Slot;

	UPROPERTY()
	class UPotionQuickSlotComponent* PotionQuickSlotComponent;

private:
	FSlot Slot;

private:
	void SetText();

public:
	void SetUpSlot();
	void BindText(class UPotionQuickSlotComponent* _PotionQuickSlotComponent);

};
