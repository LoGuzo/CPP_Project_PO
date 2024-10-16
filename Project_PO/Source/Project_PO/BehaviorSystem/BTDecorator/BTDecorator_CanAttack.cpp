// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

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

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
        return false;

    ACharacter* ControlledCharacter = Cast<ACharacter>(AIController->GetPawn());
    if (!ControlledCharacter)
        return false;

    AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(FName(TEXT("Target"))));
    if (!Target)
        return false;

    float CurrentSpeed = ControlledCharacter->GetVelocity().Size();
    float DistanceToTarget = Target->GetDistanceTo(ControlledCharacter);

    bool bCanAttack = false;

    if (CurrentSpeed >= SpeedThreshold)
    {
        if (DistanceThreshold * 1.5f <= DistanceToTarget)
            bCanAttack = true;
    }
    else
    {
        if (DistanceThreshold <= DistanceThreshold)
            bCanAttack = true;
    }

    return bResult && bCanAttack;
}
