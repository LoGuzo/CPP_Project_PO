// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EquipItemActor.h"
#include "../../../../MyEnumClass.h"
#include "BaseWeaponActor.generated.h"


UCLASS(Abstract)
class PROJECT_PO_API ABaseWeaponActor : public AEquipItemActor
{
	GENERATED_BODY()
	
public:
	ABaseWeaponActor();

protected:
	E_WeaponType WeaponType;

	UPROPERTY(VisibleAnywhere, Category = Widget)
	TSubclassOf<class UCrosshairEtcWidget> CrosshairWidget;

	UPROPERTY(VisibleAnywhere)
	class UBaseGunAnimInstance* AnimInstance;

public:
	virtual void Fire() PURE_VIRTUAL(ABaseWeaponActor::Fire, ;);

	TSubclassOf<class UCrosshairEtcWidget> GetCrosshairWdiget() const { return CrosshairWidget; }
	E_WeaponType GetWeaponType() { return WeaponType; }
	class UBaseGunAnimInstance* GetAnimInstance() { return AnimInstance; }

	FVector LineTraceFromCamera();

	virtual void SetItem(int32 _ID) override;
};
