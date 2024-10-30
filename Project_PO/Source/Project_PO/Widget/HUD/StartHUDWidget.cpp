// Fill out your copyright notice in the Description page of Project Settings.


#include "StartHUDWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Etc/SettingsWidget.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/WidgetManager.h"

UStartHUDWidget::UStartHUDWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UStartHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController) {
		SetIsFocusable(true);
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;
	}

	if (Btn_Start)
		Btn_Start->OnClicked.AddDynamic(this, &UStartHUDWidget::ClickedStart);

	if (Btn_Settings)
		Btn_Settings->OnClicked.AddDynamic(this, &UStartHUDWidget::ClickedSettings);

	if (Btn_Exit)
		Btn_Exit->OnClicked.AddDynamic(this, &UStartHUDWidget::ClickedExit);
}

void UStartHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		SetIsFocusable(false);

		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
}

void UStartHUDWidget::ClickedStart()
{
}

void UStartHUDWidget::ClickedSettings()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			USettingsWidget* SettingsWidget = WidgetManager->GetWidget<USettingsWidget>(TEXT("Settings"));
			if (SettingsWidget)
				SettingsWidget->SetAddRemove();
		}
	}
}

void UStartHUDWidget::ClickedExit()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}
