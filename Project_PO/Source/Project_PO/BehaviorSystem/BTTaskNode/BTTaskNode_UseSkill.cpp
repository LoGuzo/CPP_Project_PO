// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_UseSkill.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Character/BaseCharacter.h"
#include "../../Controller/AI/BaseAIController.h"

UBTTaskNode_UseSkill::UBTTaskNode_UseSkill()
{
	bNotifyTick = true;
	NodeName = TEXT("UseSkill");
}

EBTNodeResult::Type UBTTaskNode_UseSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (!BlackboardComponent || !AIController)
		return EBTNodeResult::Failed;

	AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(FName(TEXT("Target"))));
	int32 SkillID = BlackboardComponent->GetValueAsInt(FName(TEXT("SkillID")));
	if(!Target || SkillID == -1)
		return EBTNodeResult::Failed;

	AIController->AttackSkill(Target, SkillID);

	return Result;
}

void UBTTaskNode_UseSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
		return;

	ABaseCharacter* Character = Cast<ABaseCharacter>(AIController->GetPawn());
	if (!Character)
		return;

	if (!Character->GetIsAttack())
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
