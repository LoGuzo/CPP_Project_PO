// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanSkill.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/AI/BaseAIController.h"

UBTDecorator_CanSkill::UBTDecorator_CanSkill()
{
	NodeName = TEXT("CanSkill");
}

bool UBTDecorator_CanSkill::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComponent)
        return false;

    ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
        return false;

    AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(FName(TEXT("Target"))));
    if (Target == nullptr)
        return false;

    return bResult && AIController->CanUseSkill(Target);
}
