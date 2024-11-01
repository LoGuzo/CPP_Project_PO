// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuMainWidget.h"
#include "MenuWidget.h"
#include "Components/Button.h"

void UMenuMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(WBP_Menu->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(true);
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(true);
	}

	if (Btn_Back)
		Btn_Back->OnClicked.AddDynamic(this, &UMenuMainWidget::ClickedBackBtn);
}

void UMenuMainWidget::NativeDestruct()
{
	Super::NativeDestruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(false);
	}

	if (Btn_Back)
		Btn_Back->OnClicked.RemoveDynamic(this, &UMenuMainWidget::ClickedBackBtn);
}

void UMenuMainWidget::ClickedBackBtn()
{
	if (IsInViewport())
		RemoveFromParent();
}
