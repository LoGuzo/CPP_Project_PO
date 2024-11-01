// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseInGameWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UMenuWidget : public UBaseInGameWidget
{
	GENERATED_BODY()

public:
	UMenuWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Settings;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Inven;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Exit;

	TSubclassOf<class UPopGameExitWidget> PopGameExitWidget;

private:
	UFUNCTION()
	void ClickedSettingsBtn();

	UFUNCTION()
	void ClickedInvenBtn();

	UFUNCTION()
	void ClickedExitBtn();

	void SetAddRemoveWidget(FString const& Name);
};
