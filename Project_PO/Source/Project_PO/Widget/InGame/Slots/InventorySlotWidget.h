// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSlotWidget.h"
#include "../../../MyStructureAll.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UInventorySlotWidget : public UBaseSlotWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Slot;

private:
	int32 Amount;
	int32 ConIndex;
	FSpawnItemType Type;

public:
	void SetAmount(int32 const& _Amount) { Amount = _Amount; }
	void SetConIndex(int32 const& _ConIndex) { ConIndex = _ConIndex; }
	void SetType(FSpawnItemType const& _Type) { Type = _Type; }
};
