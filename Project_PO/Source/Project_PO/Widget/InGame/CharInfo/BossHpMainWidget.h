// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseInGameWidget.h"
#include "BossHpMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBossHpMainWidget : public UBaseInGameWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UBossHpWidget* WBP_BossHp;

public:
	void SetBossHp(class UStatComponent* StatComponent);
};
