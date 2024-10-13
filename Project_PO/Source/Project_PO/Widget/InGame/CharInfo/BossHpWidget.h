// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHpInfoWidget.h"
#include "BossHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBossHpWidget : public UBaseHpInfoWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_HpPer;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Hp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Name;

public:
	virtual void BindHp(class UStatComponent* _StatComp) override;
	virtual void UpdateHp() override;
};
