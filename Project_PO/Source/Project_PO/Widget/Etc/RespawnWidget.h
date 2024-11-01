// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEtcWidget.h"
#include "RespawnWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API URespawnWidget : public UBaseEtcWidget
{
	GENERATED_BODY()
	
public:
	URespawnWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Time;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Respawn;

private:
	float RemainingTime;

private:	
	void UpdateTimerUI(FString TimerText);
	void UpdateTimer(float _RemainingTime);

	void FindPostProcessVolume();

	UFUNCTION()
	void ClickedRespawnBtn();
};
