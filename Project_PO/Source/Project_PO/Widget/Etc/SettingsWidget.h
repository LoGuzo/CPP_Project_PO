// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEtcWidget.h"
#include "SettingsWidget.generated.h"


UCLASS()
class PROJECT_PO_API USettingsWidget : public UBaseEtcWidget
{
	GENERATED_BODY()
	
public:
	USettingsWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Audio;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Back;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_Settings;

	TSubclassOf<class UAudioSettingsWidget> AudioSettingsWidget;

private:
	UFUNCTION()
	void SetUpAudioWidget();

	UFUNCTION()
	void RemoveWidget();
};
