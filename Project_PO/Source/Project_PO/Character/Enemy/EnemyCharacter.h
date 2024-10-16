// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "../../MyStructureAll.h"
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
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	E_MonsterType MonsterType;

	UPROPERTY()
	class UBaseEnemyAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* HeadCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* BodyCollision;

private:
	void SetUpDamageWidget(class AController* PlayerController, E_DamageType const & Type, FVector const& Location, int32 const& Damage);

protected:
	void SetUpCharacter();
	virtual void SetCharacterMesh() {};
	virtual void SetUpHeadCollision();
	virtual void SetUpBodyCollision();
	virtual void SetUpArmCollision() {};
	virtual void SetUpLegCollision() {};

	virtual void Attack() {};

public:
	E_MonsterType GetMonsterType() { return MonsterType; }

	virtual void MeleeAttackCheck(float const& Range, float const& Coefficient) override;
};
