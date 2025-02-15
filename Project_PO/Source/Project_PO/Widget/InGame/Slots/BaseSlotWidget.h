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

public:
	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class USizeBox* Box_Slot;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Slot;

protected:
	int32 ID;

public:
	void SetItemID(int32 const& _ID) { ID = _ID; }
};
