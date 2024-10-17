// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/AI/BaseAIController.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComponent)
        return;

    ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
        return;

    AActor* Target = AIController->SearchTarget();

    BlackboardComponent->SetValueAsObject(FName(TEXT("Target")), Target);
}
