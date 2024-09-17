// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../MyEnumClass.h"
#include "BaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBaseUserWidget(const FObjectInitializer& ObjectInitializer);

protected:
	E_WidgetType Type;

public:
	virtual void InitializeWidget();
	void SetShowHidden();
	void SetAddRemove();
};
