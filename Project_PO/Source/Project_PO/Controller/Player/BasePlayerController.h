// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../../MyEnumClass.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UMyHUDWidget> HUDWidget;
	TSubclassOf<class UMainInventoryWidget> InventoryWidget;
	TSubclassOf<class UDamagePopUpWidget> DamagePopUpWidget;
	TSubclassOf<class UAccessAlertWidget> AccessAlertWidget;
	TSubclassOf<class UBossHpMainWidget> BossHpMainWidget;
	TSubclassOf<class UTimerWidget> TimerWidget;

	UPROPERTY()
	class ULevelSequencePlayer* Sequence;

private:
	void SetUpWidget();
	UFUNCTION()
	void SequenceFinished();

public:
	void SetUpDamageWidget(E_DamageType const& Type, FVector const& Location,int32 const& Damage);
	void SetUpTimerWidget(float const& RemainingTime);

	void AddRemoveWidget(FString const& WidgetName);
	void ShowHideWidget(FString const& WidgetName);

	void PlaySequence(class ULevelSequencePlayer* SequencePlayer);
};
