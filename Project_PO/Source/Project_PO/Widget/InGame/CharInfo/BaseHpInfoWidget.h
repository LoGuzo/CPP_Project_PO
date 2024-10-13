// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseInGameWidget.h"
#include "BaseHpInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBaseHpInfoWidget : public UBaseInGameWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Hp;

protected:
	class UStatComponent* StatComponent;

public:
	virtual void BindHp(class UStatComponent* _StatComp);
	virtual void UpdateHp();
};
