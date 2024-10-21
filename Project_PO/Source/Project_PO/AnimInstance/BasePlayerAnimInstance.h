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
	bool bIsSprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (AllowPrivateAccess = "true"))
	float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (AllowPrivateAccess = "true"))
	float PlayerRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Type, meta = (AllowPrivateAccess = "true"))
	E_WeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IK, meta = (AllowPrivateAccess = "true"))
	FTransform LeftHandSocketTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IK, meta = (AllowPrivateAccess = "true"))
	FTransform RightHandSocketTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IK, meta = (AllowPrivateAccess = "true"))
	FVector JointTargetLocation;

public:
	bool GetIsArmed() { return bIsArmed; }
	void SetIsArmed(bool _bIsArmed) { bIsArmed = _bIsArmed; }

	bool GetIsAiming() { return bIsAiming; }
	void SetIsAiming(bool _bIsAiming) { bIsAiming = _bIsAiming; }

	bool GetIsSprint() { return bIsSprint; }
	void SetIsSprint(bool _bIsSprint) { bIsSprint = _bIsSprint; }

	E_WeaponType GetWeaponType(){ return WeaponType; }
	void SetWeaponType(E_WeaponType _WeaponType) { WeaponType = _WeaponType; }

	UFUNCTION()
	void AnimNotify_PotionEnd();
};
