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

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UBossHpMainWidget> BossHpMainWidget;

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
	void SetUpBossHp();
	void VisibleWidget();

protected:
	virtual void SetUpArmCollision() override;
	virtual void SetUpLegCollision() override;

	virtual void SetState(bool NowState) override;
};
