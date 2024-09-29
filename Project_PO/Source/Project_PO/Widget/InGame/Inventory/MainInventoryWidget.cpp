// Fill out your copyright notice in the Description page of Project Settings.


#include "MainInventoryWidget.h"
#include "InventoryWidget.h"
#include "../../../Character/Player/PlayerCharacter.h"
#include "../../../Component/InventoryComponent.h"

void UMainInventoryWidget::NativeConstruct()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController) {

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(WBP_Inventory->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(true);
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(true);

		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetCharacter());
		if (PlayerCharacter)
		{
			UInventoryComponent* InventoryComponent = PlayerCharacter->GetInventoryComponent();
			if (InventoryComponent)
				WBP_Inventory->UpdateInventory(InventoryComponent);
		}
	}
}

void UMainInventoryWidget::NativeDestruct()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController) {

		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(false);
	}
}
