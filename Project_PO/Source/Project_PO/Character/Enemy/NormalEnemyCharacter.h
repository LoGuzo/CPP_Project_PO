// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "NormalEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ANormalEnemyCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	ANormalEnemyCharacter();

protected:
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* HpBar;

	UPROPERTY()
	class UBaseHpInfoWidget* OnlyHpBar;

private:
	void VisibleHpBar();

public:
	virtual void Died() override;
};
