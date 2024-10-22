// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTriggerBox.h"
#include "BossTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABossTriggerBox : public ABaseTriggerBox
{
	GENERATED_BODY()

public:
	ABossTriggerBox();

protected:
	virtual void SpawnMonster() override;
	virtual void DeSpawnMonster() override;
	virtual void SetUpTrigger() override;
};
