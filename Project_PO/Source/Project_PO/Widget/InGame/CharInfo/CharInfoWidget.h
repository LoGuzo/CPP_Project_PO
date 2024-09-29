// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHpInfoWidget.h"
#include "CharInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UCharInfoWidget : public UBaseHpInfoWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Mp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Exp;

public:
	void BindMp(class UStatComponent* _StatComp);
	void UpdateMp();

	void BindExp(class UStatComponent* _StatComp);
	void UpdateExp();
};
