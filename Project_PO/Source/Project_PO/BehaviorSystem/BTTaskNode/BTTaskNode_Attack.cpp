// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Character/BaseCharacter.h"
#include "../../Controller/AI/BaseAIController.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	bNotifyTick = true;
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
		return EBTNodeResult::Failed;


	ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
		return EBTNodeResult::Failed;

	AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(FName(TEXT("Target"))));
	if (!Target)
		return EBTNodeResult::Failed;

	AIController->Attack(Target);

	return Result;
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
		return;

	ABaseCharacter* Character = Cast<ABaseCharacter>(AIController->GetPawn());
	if (!Character)
		return;

	if (!Character->GetIsAttack())
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
