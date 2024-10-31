// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "../../MyEnumClass.h"
#include "BaseStagePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABaseStagePlayerController : public ABasePlayerController
{
	GENERATED_BODY()
	
public:
	ABaseStagePlayerController();

protected:
	virtual void InitPlayerState() override;
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UMyHUDWidget> HUDWidget;
	TSubclassOf<class UDamagePopUpWidget> DamagePopUpWidget;
	TSubclassOf<class UWeaponSelectWidget> WeaponSelectWidget;

	UPROPERTY()
	class ULevelSequencePlayer* Sequence;

	E_ClassType ClassType;

private:
	void SetUpWidget();
	UFUNCTION()
	void SequenceFinished();

	void SetupClassType();

public:
	void SetUpDamageWidget(E_DamageType const& Type, FVector const& Location, int32 const& Damage);
	void SetUpTimerWidget(float const& RemainingTime);

	void AddRemoveWidget(FString const& WidgetName);
	void ShowHideWidget(FString const& WidgetName);

	void PlaySequence(class ULevelSequencePlayer* SequencePlayer);

	void SetUpWeaponSelectWidget();

	void SetClassType(E_ClassType const& _ClassType) { ClassType = _ClassType; }
	E_ClassType GetClassType() { return ClassType; }
};
