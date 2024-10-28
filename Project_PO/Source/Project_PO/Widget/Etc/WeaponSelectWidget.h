// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEtcWidget.h"
#include "WeaponSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UWeaponSelectWidget : public UBaseEtcWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Pistol;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Rifle;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Shotgun;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Select;

private:
	int32 WeaponID;

private:
	UFUNCTION()
	void PistolBtn();
	UFUNCTION()
	void RifleBtn();
	UFUNCTION()
	void ShotgunBtn();

	UFUNCTION()
	void SelectWeapon();
};
