// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_UseSkill.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBTTaskNode_UseSkill : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_UseSkill();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
