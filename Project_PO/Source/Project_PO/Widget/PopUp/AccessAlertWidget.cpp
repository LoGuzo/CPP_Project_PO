// Fill out your copyright notice in the Description page of Project Settings.


#include "AccessAlertWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"

UAccessAlertWidget::UAccessAlertWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsFocusable = true;
}

void UAccessAlertWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;

		if (ACharacter* Character = Cast<ACharacter>(PlayerController->GetPawn()))
			Character->GetCharacterMovement()->DisableMovement();
	}
}

void UAccessAlertWidget::NativeDestruct()
{
	Super::NativeDestruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;

		if (ACharacter* Character = Cast<ACharacter>(PlayerController->GetPawn()))
			Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}

FReply UAccessAlertWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::G)
	{
		RemoveFromParent();
		return FReply::Handled();
	}
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UAccessAlertWidget::SetUpText(E_Access _Type)
{
	if (Txt_Access)
	{
		switch (_Type)
		{
		case E_Access::E_QuestAccess:
			Txt_Access->SetText(FText::FromString(TEXT("The quest requirements have not been met.")));
			break;
		case E_Access::E_ItemAccess:
			Txt_Access->SetText(FText::FromString(TEXT("The Item requirements have not been met.")));
			break;
		default:
			break;
		}
	}
}