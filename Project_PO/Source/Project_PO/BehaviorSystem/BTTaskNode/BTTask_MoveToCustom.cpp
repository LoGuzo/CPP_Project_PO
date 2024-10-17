// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToCustom.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/AI/BaseAIController.h"

UBTTask_MoveToCustom::UBTTask_MoveToCustom()
{
	bNotifyTick = true;
}

void UBTTask_MoveToCustom::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
		return;

	ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
		return;
	
	AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(FName(TEXT("Target"))));
	if (!Target)
		return;

	if(AIController->CanAttack(Target))
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}