// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNormalAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

ABaseNormalAIController::ABaseNormalAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT(TEXT("/Game/ThirdPerson/Blueprints/AI/BehaviorTree/BT_NormalEnemyBase.BT_NormalEnemyBase"));
	if (BT.Succeeded())
		EnemyBehaviorTree = BT.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BD(TEXT("/Game/ThirdPerson/Blueprints/AI/BlackBoard/BB_Mummy.BB_Mummy"));
	if (BD.Succeeded())
		EnemyBlackboradData = BD.Object;
}