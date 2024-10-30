// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsWidget.h"
#include "AudioSettingsWidget.h"
#include "Components/Button.h"
#include "Components/Border.h"

USettingsWidget::USettingsWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget>AudioSettings(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/Settings/WBP_AudioSettings.WBP_AudioSettings_C"));
	if (AudioSettings.Succeeded())
		AudioSettingsWidget = AudioSettings.Class;
}

void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetUpAudioWidget();

	if (Btn_Audio)
		Btn_Audio->OnClicked.AddDynamic(this, &USettingsWidget::SetUpAudioWidget);

	if (Btn_Back)
		Btn_Back->OnClicked.AddDynamic(this, &USettingsWidget::RemoveWidget);
}

void USettingsWidget::SetUpAudioWidget()
{
	if (Border_Settings)
	{
		Border_Settings->ClearChildren();

		UAudioSettingsWidget* AudioWidget = CreateWidget<UAudioSettingsWidget>(this, AudioSettingsWidget);
		if (AudioWidget)
			Border_Settings->AddChild(AudioWidget);
	}
}

void USettingsWidget::RemoveWidget()
{
	if(IsInViewport())
		RemoveFromParent();
}
