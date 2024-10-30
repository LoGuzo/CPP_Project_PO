// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEtcWidget.h"
#include "AudioSettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UAudioSettingsWidget : public UBaseEtcWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Mute;

	UPROPERTY(meta = (BindWidget))
	class USlider* Slider_All;

	UPROPERTY()
	class UAudioManager* AudioManager;

private:
	void SetAudioManager();

	void SetUpSlider();
	UFUNCTION()
	void ChangedVolume(float Volume);

	UFUNCTION()
	void MuteVolume();
};
