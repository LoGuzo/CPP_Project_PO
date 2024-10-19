// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

ABaseBossAIController::ABaseBossAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT(TEXT("/Game/ThirdPerson/Blueprints/AI/BehaviorTree/BT_BoseBase.BT_BoseBase"));
	if (BT.Succeeded())
		EnemyBehaviorTree = BT.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BD(TEXT("/Game/ThirdPerson/Blueprints/AI/BlackBoard/BB_Base.BB_Base"));
	if (BD.Succeeded())
		EnemyBlackboradData = BD.Object;
}
