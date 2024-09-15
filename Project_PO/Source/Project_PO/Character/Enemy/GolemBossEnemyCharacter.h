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

private:
	void SetCharacterMesh();
	void SetUpHeadCollision();
	void SetUpArmCollision();
	void SetUpLegCollision();
};
