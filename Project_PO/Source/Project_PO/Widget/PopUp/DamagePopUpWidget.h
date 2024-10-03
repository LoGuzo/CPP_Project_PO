// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePopUpWidget.h"
#include "DamagePopUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UDamagePopUpWidget : public UBasePopUpWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Damage;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* DamageAnim;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* CriticalAnim;

	UPROPERTY()
	FTimerHandle ReleaseTimerHandle;

private:
	void ReleaseTimer();

public:
	void SetDamageText(int32 const& Damage);
	void SetCriticalText(int32 const& Damage);

	void Release();
};
