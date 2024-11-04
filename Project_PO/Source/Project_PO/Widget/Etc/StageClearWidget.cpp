// Fill out your copyright notice in the Description page of Project Settings.


#include "StageClearWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UStageClearWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(true);
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(true);
	}

	if (Btn_MainMenu)
		Btn_MainMenu->OnClicked.AddDynamic(this, &UStageClearWidget::ClickedMainMenuBtn);
}

void UStageClearWidget::NativeDestruct()
{
	Super::NativeDestruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(false);
	}

	if (Btn_MainMenu)
		Btn_MainMenu->OnClicked.RemoveDynamic(this, &UStageClearWidget::ClickedMainMenuBtn);
}

void UStageClearWidget::ClickedMainMenuBtn()
{
	UGameplayStatics::OpenLevel(this, FName("GameStart"));
}