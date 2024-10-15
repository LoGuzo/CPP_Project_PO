// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseAIController::ABaseAIController()
{
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (!BlackboardComponent)
		return;

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
