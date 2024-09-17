// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseUserWidget.h"
#include "CrosshairEtcWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UCrosshairEtcWidget : public UBaseUserWidget
{
	GENERATED_BODY()
	
public:
	UCrosshairEtcWidget(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(meta = (BindWidget))
	class UBorder* CenterCrosshair;
	
	UPROPERTY(meta = (BindWidget))
	class UBorder* TopCrosshair;
	
	UPROPERTY(meta = (BindWidget))
	class UBorder* BottomCrosshair;
	
	UPROPERTY(meta = (BindWidget))
	class UBorder* RightCrosshair;
	
	UPROPERTY(meta = (BindWidget))
	class UBorder* LeftCrosshair;

};
