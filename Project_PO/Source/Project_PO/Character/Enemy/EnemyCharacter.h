// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

protected:
	UPROPERTY()
	class UBaseEnemyAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* HeadCollision;

private:
	void SetUpHeadCollision();
};
