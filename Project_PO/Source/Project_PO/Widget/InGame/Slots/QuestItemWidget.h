// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSlotWidget.h"
#include "QuestItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UQuestItemWidget : public UBaseSlotWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Slot;

private:
	int32 Amount;

public:
	void SetAmount(int32 const& _Amount) { Amount = _Amount; }
};
