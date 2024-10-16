// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CanAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBTDecorator_CanAttack : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_CanAttack();

protected:
	UPROPERTY(EditAnywhere, Category = "Attack Condition")
	float SpeedThreshold;

	UPROPERTY(EditAnywhere, Category = "Attack Condition")
	float DistanceThreshold;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
