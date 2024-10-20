// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToCustom.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBTTask_MoveToCustom : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	UBTTask_MoveToCustom();

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float ChkTime;
	float CurTime;
};
