// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAnimInstance.h"
#include "BasePlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBasePlayerAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UBasePlayerAnimInstance();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Type)
	E_WeaponType WeaponType;
};
