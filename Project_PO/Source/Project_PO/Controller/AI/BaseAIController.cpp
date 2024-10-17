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

void ABaseAIController::Attack()
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (!EnemyCharacter)
		return;

	EnemyCharacter->Attack();
}

AActor* ABaseAIController::SearchTarget()
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (!EnemyCharacter)
		return nullptr;

	return EnemyCharacter->SearchTarget();
}

bool ABaseAIController::CanAttack(AActor const* _Target)
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (!EnemyCharacter)
		return false;

	return EnemyCharacter->CanAttack(_Target);
}

bool ABaseAIController::CanUseSkill(AActor const* _Target)
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (!EnemyCharacter)
		return false;

	return EnemyCharacter->CanUseSkill(_Target);
}