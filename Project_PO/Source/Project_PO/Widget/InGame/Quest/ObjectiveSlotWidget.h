// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseInGameWidget.h"
#include "ObjectiveSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UObjectiveSlotWidget : public UBaseInGameWidget
{
	GENERATED_BODY()
	
public:
	UObjectiveSlotWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Objective;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Description;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Amount;

private:
	int32 ObjectiveID;

private:
	void UpdateWidget();
	void BindWidget(int32 _ObjectiveID);
public:
	void SetUpWidget(int32 _ObjectiveID);
};
