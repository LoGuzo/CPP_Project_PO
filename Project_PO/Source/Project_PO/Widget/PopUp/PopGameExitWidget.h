// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePopUpWidget.h"
#include "PopGameExitWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UPopGameExitWidget : public UBasePopUpWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Yes;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_No;

private:
	UFUNCTION()
	void ClickedYesBtn();

	UFUNCTION()
	void ClickedNoBtn();
};
