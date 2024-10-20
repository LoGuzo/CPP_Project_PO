// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToCustom.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Character/Enemy/EnemyCharacter.h"
#include "../../Component/StatComponent/MonsterStatComponent.h"
#include "../../Controller/AI/BaseAIController.h"

UBTTask_MoveToCustom::UBTTask_MoveToCustom()
{
	bNotifyTick = true;
	ChkTime = 1.f;
	CurTime = 0.f;
}

void UBTTask_MoveToCustom::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	CurTime += DeltaSeconds;

	if (CurTime >= ChkTime)
	{
		UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
		if (!BlackboardComponent)
			return;

		ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
		if (!AIController)
			return;

		AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(FName(TEXT("Target"))));
		if (!Target)
			return;

		int32 DummyInt;

		CurTime = 0;

		if (AIController->CanUseSkill(Target, DummyInt))
		{
			AIController->StopMovement();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return;
		}

		if (AIController->CanAttack(Target))
		{
			AIController->StopMovement();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return;
		}
	}
}