// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Attack.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
	: blsAttacking(false)
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}
