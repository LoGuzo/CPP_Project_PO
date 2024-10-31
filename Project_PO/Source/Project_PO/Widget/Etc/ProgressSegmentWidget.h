// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEtcWidget.h"
#include "ProgressSegmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UProgressSegmentWidget : public UBaseEtcWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_1;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_2;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_3;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_4;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_5;

public:
	void SetSegment(float const& Value);
};
