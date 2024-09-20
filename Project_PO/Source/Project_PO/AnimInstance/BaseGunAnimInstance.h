// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseGunAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBaseGunAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UBaseGunAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* GunAttackMontage;

public:
	void OnGunAttackPlayAM();
};
