// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTriggerBox.h"
#include "StageClearTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AStageClearTriggerBox : public ABaseTriggerBox
{
	GENERATED_BODY()
	
public:
	AStageClearTriggerBox();

protected:
	virtual void SetUpTrigger() override;
	virtual void SetLevelSequence() override;

private:
	void SetStateAllPlayer(bool const& bState);
};
