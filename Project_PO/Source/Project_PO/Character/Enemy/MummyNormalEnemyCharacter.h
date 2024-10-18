// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NormalEnemyCharacter.h"
#include "MummyNormalEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AMummyNormalEnemyCharacter : public ANormalEnemyCharacter
{
	GENERATED_BODY()
	
public:
	AMummyNormalEnemyCharacter();

private:
	virtual void SetCharacterMesh() override;
	virtual void SetUpHeadCollision() override;
	virtual void SetUpBodyCollision() override;

public:
	virtual void Attack(AActor* _Target) override;
	virtual	AActor* SearchTarget() override;
	virtual bool CanAttack(AActor* _Target) override;
};
