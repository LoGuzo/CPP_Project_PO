// Fill out your copyright notice in the Description page of Project Settings.


#include "PopGameExitWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UPopGameExitWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Yes)
		Btn_Yes->OnClicked.AddDynamic(this, &UPopGameExitWidget::ClickedYesBtn);

	if (Btn_No)
		Btn_No->OnClicked.AddDynamic(this, &UPopGameExitWidget::ClickedNoBtn);
}

void UPopGameExitWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (Btn_Yes)
		Btn_Yes->OnClicked.RemoveDynamic(this, &UPopGameExitWidget::ClickedYesBtn);

	if (Btn_No)
		Btn_No->OnClicked.RemoveDynamic(this, &UPopGameExitWidget::ClickedNoBtn);
}

void UPopGameExitWidget::ClickedYesBtn()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}

void UPopGameExitWidget::ClickedNoBtn()
{
	if (IsInViewport())
		RemoveFromParent();
}
