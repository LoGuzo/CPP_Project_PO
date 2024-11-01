// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectWidget.h"
#include "CharacterSlotWidget.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"


UCharacterSelectWidget::UCharacterSelectWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget>CharSlot(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/CharacterSelect/WBP_CharacterSlot.WBP_CharacterSlot_C"));
	if (CharSlot.Succeeded())
		CharSlotWidget = CharSlot.Class;
}

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController) {
		SetIsFocusable(true);
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		PlayerController->SetInputMode(InputMode);
	}

	if (Btn_Select)
	{
		Btn_Select->OnClicked.AddDynamic(this, &UCharacterSelectWidget::ClickedCharSelect);
		Btn_Select->SetIsEnabled(false);
	}

	if (Btn_Back)
		Btn_Back->OnClicked.AddDynamic(this, &UCharacterSelectWidget::ClickedBackBtn);

	UpdatesSlots();
}

void UCharacterSelectWidget::UpdatesSlots()
{
	if (Wrap_Chars)
	{
		Wrap_Chars->ClearChildren();
		for (size_t i = 1; i < 4; i++)
		{
			if (CharSlotWidget)
			{
				UCharacterSlotWidget* SlotWidget = CreateWidget<UCharacterSlotWidget>(this, CharSlotWidget);
				if (SlotWidget)
				{
					SlotWidget->SetClassID(i);
					SlotWidget->GetBtn()->OnClicked.AddDynamic(this, &UCharacterSelectWidget::ClickedCharBtn);
					Wrap_Chars->AddChild(SlotWidget);
				}
			}
		}
	}
}

void UCharacterSelectWidget::ClickedCharSelect()
{
	UGameplayStatics::OpenLevel(this, FName("Sky_Dungeon_Demo"));
}

void UCharacterSelectWidget::ClickedBackBtn()
{
	if (IsInViewport())
		RemoveFromParent();
}

void UCharacterSelectWidget::ClickedCharBtn()
{
	if (Btn_Select)
		Btn_Select->SetIsEnabled(true);
}