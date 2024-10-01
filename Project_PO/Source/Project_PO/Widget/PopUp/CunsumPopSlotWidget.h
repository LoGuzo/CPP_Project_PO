// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePopSlotWidget.h"
#include "CunsumPopSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UCunsumPopSlotWidget : public UBasePopSlotWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Register;

private:
	UFUNCTION()
	void UseItem();

	UFUNCTION()
	void RegisterItem();
};
