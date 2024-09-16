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

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool bIsArmed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool bIsAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (AllowPrivateAccess = "true"))
	float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Type, meta = (AllowPrivateAccess = "true"))
	E_WeaponType WeaponType;

public:
	bool GetIsArmed() { return bIsArmed; }
	void SetIsArmed(bool _bIsArmed) { bIsArmed = _bIsArmed; }

	bool GetIsAiming() { return bIsAiming; }
	void SetIsAiming(bool _bIsAiming) { bIsAiming = _bIsAiming; }
};
