// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/PostProcessVolume.h"
#include "../../Character/Player/PlayerCharacter.h"

URespawnWidget::URespawnWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, RemainingTime(0.f)
{
}

void URespawnWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (RemainingTime > 0.f)
	{
		UpdateTimer(RemainingTime);

		RemainingTime -= InDeltaTime;
	}
	else
	{
		if (Btn_Respawn)
		{
			if (!Btn_Respawn->GetIsEnabled())
				Btn_Respawn->SetIsEnabled(true);
		}
	}
}

void URespawnWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController) {
		SetIsFocusable(true);
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(true);
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(true);
	}

	RemainingTime = 10.f;

	if (Btn_Respawn)
	{
		Btn_Respawn->SetIsEnabled(false);
		Btn_Respawn->OnClicked.AddDynamic(this, &URespawnWidget::ClickedRespawnBtn);
	}
}

void URespawnWidget::NativeDestruct()
{
	Super::NativeDestruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController) {
		SetIsFocusable(false);
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(false);
	}
}

void URespawnWidget::UpdateTimerUI(FString TimerText)
{
	if (Txt_Time)
		Txt_Time->SetText(FText::FromString(TimerText));
}

void URespawnWidget::UpdateTimer(float _RemainingTime)
{
	int32 Minutes = FMath::FloorToInt(_RemainingTime / 60);
	int32 Seconds = FMath::FloorToInt(_RemainingTime) % 60;

	FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	UpdateTimerUI(TimeString);
}

void URespawnWidget::ClickedRespawnBtn()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayer()->GetPawn());
	if (PlayerCharacter)
		PlayerCharacter->Respawn();

	if (IsInViewport())
		RemoveFromParent();
}