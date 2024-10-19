// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FocusTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/AI/BaseAIController.h"

UBTTaskNode_FocusTarget::UBTTaskNode_FocusTarget()
{
	NodeName = TEXT("FocusTarget");
}

EBTNodeResult::Type UBTTaskNode_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (!BlackboardComponent || !AIController)
		return EBTNodeResult::Failed;

	AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(FName(TEXT("Target"))));
	if (!Target)
		return EBTNodeResult::Failed;

	AIController->SetFocus(Target);

	return EBTNodeResult::Succeeded;
}
