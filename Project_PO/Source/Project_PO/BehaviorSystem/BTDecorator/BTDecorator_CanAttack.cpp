// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/AI/BaseAIController.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
    NodeName = TEXT("Can Attack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComponent)
        return false;

    ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
        return false;

    AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(FName(TEXT("Target"))));
    if (!Target)
        return false;

    return bResult && AIController->CanAttack(Target);
}
