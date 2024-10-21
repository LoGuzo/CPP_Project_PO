// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerWidget.h"
#include "Components/TextBlock.h"

UTimerWidget::UTimerWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RemainingTime = 0.f;
}

void UTimerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (RemainingTime > 0.f)
	{
		UpdateTimer(RemainingTime);

		RemainingTime -= InDeltaTime;
	}
}

void UTimerWidget::UpdateTimerUI(FString TimerText)
{
	if (Txt_Timer)
		Txt_Timer->SetText(FText::FromString(TimerText));
}

void UTimerWidget::UpdateTimer(float _RemainingTime)
{
	int32 Minutes = FMath::FloorToInt(_RemainingTime / 60);
	int32 Seconds = FMath::FloorToInt(_RemainingTime) % 60;

	FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	UpdateTimerUI(TimeString);
}