// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHUDWidget.h"
#include "StartHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UStartHUDWidget : public UBaseHUDWidget
{
	GENERATED_BODY()
	
public:
	UStartHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Start;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Settings;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Exit;

	TSubclassOf<class UCharacterSelectWidget> CharSelectWidget;

private:
	UFUNCTION()
	void ClickedStart();

	UFUNCTION()
	void ClickedSettings();

	UFUNCTION()
	void ClickedExit();
};
