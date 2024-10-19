// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABaseAIController();

public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

protected:
	UPROPERTY()
	class UBehaviorTree* EnemyBehaviorTree;
	UPROPERTY()
	class UBlackboardData* EnemyBlackboradData;

public:
	virtual void Attack(AActor* _Target);
	virtual void AttackSkill(AActor* _Target, int32 const& SkillID);
	virtual AActor* SearchTarget();
	virtual bool CanAttack(AActor* _Target);
	bool CanUseSkill(AActor* _Target, int32& SkillID);
};
