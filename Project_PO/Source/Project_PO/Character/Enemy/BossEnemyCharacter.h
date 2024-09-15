// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "BossEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABossEnemyCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	ABossEnemyCharacter();

private:
	int32 MonsterID;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* RightArmCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* LeftArmCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* RightLegCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* LeftLegCollision;

private:
	void SetUpArmCollision();
	void SetUpLegCollision();
};
