// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseUserWidget.h"
#include "BaseHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBaseHUDWidget : public UBaseUserWidget
{
	GENERATED_BODY()
	
public:
	UBaseHUDWidget(const FObjectInitializer& ObjectInitializer);
};
