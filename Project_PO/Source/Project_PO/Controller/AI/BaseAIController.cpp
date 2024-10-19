// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Character/Enemy/EnemyCharacter.h"

ABaseAIController::ABaseAIController()
{
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (!UseBlackboard(EnemyBlackboradData, BlackboardComponent))
		return;

	if (!RunBehaviorTree(EnemyBehaviorTree))
		return;
}

void ABaseAIController::OnUnPossess()
{
	Super::OnUnPossess();

    UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (BehaviorTreeComponent)
        BehaviorTreeComponent->StopTree(EBTStopMode::Safe);

    UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
    if (BlackboardComponent)
        BlackboardComponent->ClearValue("Target");
}

void ABaseAIController::Attack(AActor* _Target)
{
	if (!_Target)
		return;

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (!EnemyCharacter)
		return;

	SetFocus(_Target);

	EnemyCharacter->Attack(_Target);

	ClearFocus(EAIFocusPriority::Gameplay);

}

void ABaseAIController::AttackSkill(AActor* _Target, int32 const& SkillID)
{
	if (!_Target)
		return;

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (!EnemyCharacter)
		return;

	ClearFocus(EAIFocusPriority::Gameplay);

	EnemyCharacter->AttackSkill(_Target, SkillID);
}

AActor* ABaseAIController::SearchTarget()
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (!EnemyCharacter)
		return nullptr;

	return EnemyCharacter->SearchTarget();
}

bool ABaseAIController::CanAttack(AActor* _Target)
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (!EnemyCharacter)
		return false;

	return EnemyCharacter->CanAttack(_Target);
}

bool ABaseAIController::CanUseSkill(AActor* _Target, int32& SkillID)
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (!EnemyCharacter)
	{
		SkillID = -1;
		return false;
	}

	return EnemyCharacter->CanUseSkill(_Target, SkillID);
}