// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CanSkill.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBTDecorator_CanSkill : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_CanSkill();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
