// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSettingsWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/AudioManager.h"

void UAudioSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Slider_All)
		Slider_All->OnValueChanged.AddDynamic(this, &UAudioSettingsWidget::ChangedVolume);

	if (Btn_Mute)
		Btn_Mute->OnClicked.AddDynamic(this, &UAudioSettingsWidget::MuteVolume);

	SetAudioManager();
}

void UAudioSettingsWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (Slider_All)
		Slider_All->OnValueChanged.RemoveDynamic(this, &UAudioSettingsWidget::ChangedVolume);

	if (Btn_Mute)
		Btn_Mute->OnClicked.RemoveDynamic(this, &UAudioSettingsWidget::MuteVolume);

	if (AudioManager)
		AudioManager = nullptr;
}

void UAudioSettingsWidget::SetAudioManager()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
		AudioManager = GameInstance->GetManager<UAudioManager>(E_ManagerType::E_AudioManager);

	SetUpSlider();
}

void UAudioSettingsWidget::SetUpSlider()
{
	if (AudioManager)
		Slider_All->SetValue(AudioManager->GetVolume());
}

void UAudioSettingsWidget::ChangedVolume(float Volume)
{
	if (AudioManager)
		AudioManager->SetVolume(Volume);
}

void UAudioSettingsWidget::MuteVolume()
{
	ChangedVolume(0);

	SetUpSlider();
}