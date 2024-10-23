// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossEnemyCharacter.h"
#include "GolemBossEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AGolemBossEnemyCharacter : public ABossEnemyCharacter
{
	GENERATED_BODY()
	
public:
	AGolemBossEnemyCharacter();

protected:
	virtual void BeginPlay() override;

private:
	virtual void SetCharacterMesh() override;
	virtual void SetUpHeadCollision() override;
	virtual void SetUpArmCollision() override;
	virtual void SetUpLegCollision() override;
	virtual void SetUpBodyCollision() override;

public:
	virtual void Died() override;
	virtual void Attack(AActor* _Target) override;
	virtual void SetState(bool NowState) override;
};
