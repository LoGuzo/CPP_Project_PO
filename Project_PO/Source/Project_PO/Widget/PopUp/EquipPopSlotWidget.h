// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePopSlotWidget.h"
#include "EquipPopSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UEquipPopSlotWidget : public UBasePopSlotWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void EquipItem();

};
