// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseInGameWidget.h"
#include "DragWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UDragWidget : public UBaseInGameWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Drag;

private:
	int32 ID;

public:
	void SetID(int32 const& _ID) { ID = _ID; }
};
