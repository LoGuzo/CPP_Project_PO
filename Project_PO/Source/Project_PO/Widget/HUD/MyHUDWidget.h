// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHUDWidget.h"
#include "../../MyEnumClass.h"
#include "MyHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UMyHUDWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

public:
	UMyHUDWidget(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(meta = (BindWidget))
	class UCharInfoWidget* WBP_CharInfo;

public:
	void SetUpCharInfo(class UStatComponent* StatComponent);
};
