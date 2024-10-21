// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEtcWidget.h"
#include "TimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UTimerWidget : public UBaseEtcWidget
{
	GENERATED_BODY()
	
public:
	UTimerWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Timer;

private:
	float RemainingTime;

private:
	void UpdateTimerUI(FString TimerText);
	void UpdateTimer(float _RemainingTime);

public:
	void SetReminingTime(float _RemainingTime) { RemainingTime = _RemainingTime; }
};
