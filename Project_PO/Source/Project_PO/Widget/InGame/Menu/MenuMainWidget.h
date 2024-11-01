// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseInGameWidget.h"
#include "MenuMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UMenuMainWidget : public UBaseInGameWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Back;

	UPROPERTY(meta = (BindWidget))
	class UMenuWidget* WBP_Menu;

private:
	UFUNCTION()
	void ClickedBackBtn();
};
