// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseUserWidget.h"
#include "BaseInGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBaseInGameWidget : public UBaseUserWidget
{
	GENERATED_BODY()
	
public:
	UBaseInGameWidget(const FObjectInitializer& ObjectInitializer);
};
