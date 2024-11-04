// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEtcWidget.h"
#include "StageClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UStageClearWidget : public UBaseEtcWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_MainMenu;

private:
	UFUNCTION()
	void ClickedMainMenuBtn();
};
