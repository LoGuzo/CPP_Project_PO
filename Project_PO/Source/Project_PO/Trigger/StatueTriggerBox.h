// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTriggerBox.h"
#include "StatueTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AStatueTriggerBox : public ABaseTriggerBox
{
	GENERATED_BODY()

protected:
	virtual void SetUpTrigger() override;

	virtual void SpawnMonster() override;

	UPROPERTY(EditAnywhere, Category = "Target", meta = (AllowPrivateAccess = true))
	AActor* Target;

	void SetUpStatue();

public:
	void DeSpawnMonster();
};
