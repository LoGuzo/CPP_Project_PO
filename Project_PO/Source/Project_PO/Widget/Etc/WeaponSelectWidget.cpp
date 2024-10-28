// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSelectWidget.h"
#include "Components/Button.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "../../Character/Player/PlayerCharacter.h"
#include "../../Component/InventoryComponent.h"

void UWeaponSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		SetIsFocusable(true);

		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;

		if (ACharacter* Character = Cast<ACharacter>(PlayerController->GetPawn()))
			Character->GetCharacterMovement()->DisableMovement();
	}

	if (Btn_Pistol)
		Btn_Pistol->OnClicked.AddDynamic(this, &UWeaponSelectWidget::PistolBtn);

	if (Btn_Rifle)
		Btn_Rifle->OnClicked.AddDynamic(this, &UWeaponSelectWidget::RifleBtn);

	if (Btn_Shotgun)
		Btn_Shotgun->OnClicked.AddDynamic(this, &UWeaponSelectWidget::ShotgunBtn);

	if (Btn_Select)
		Btn_Select->OnClicked.AddDynamic(this, &UWeaponSelectWidget::SelectWeapon);
}

void UWeaponSelectWidget::NativeDestruct()
{
	Super::NativeDestruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		SetIsFocusable(false);

		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;

		if (ACharacter* Character = Cast<ACharacter>(PlayerController->GetPawn()))
			Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}

void UWeaponSelectWidget::PistolBtn()
{
	WeaponID = 1000;
}

void UWeaponSelectWidget::RifleBtn()
{
	WeaponID = 1001;
}

void UWeaponSelectWidget::ShotgunBtn()
{
	WeaponID = 1002;
}

void UWeaponSelectWidget::SelectWeapon()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayer()->GetPawn());
	if (!PlayerCharacter)
		return;

	PlayerCharacter->SetEquip(WeaponID);

	RemoveFromParent();
}