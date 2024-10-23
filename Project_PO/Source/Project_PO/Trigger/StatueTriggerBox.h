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

public:
	AStatueTriggerBox();

protected:
	UPROPERTY(EditAnywhere, Category = "Target", meta = (AllowPrivateAccess = true))
	AActor* Target;

protected:
	virtual void SetUpTrigger() override;
	virtual void SpawnMonster() override;
	virtual void DeSpawnMonster() override;
	virtual void QuestClear() override;

protected:
	void SetUpStatue();

	void ClearBroadCast();
};
