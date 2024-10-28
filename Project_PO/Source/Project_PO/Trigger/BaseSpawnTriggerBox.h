// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTriggerBox.h"
#include "../Interface/Teleportable.h"
#include "BaseSpawnTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABaseSpawnTriggerBox : public ABaseTriggerBox, public ITeleportable
{
	GENERATED_BODY()
	
public:
	ABaseSpawnTriggerBox();

protected:
	UFUNCTION()
	virtual void Teleport() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	TArray<class ABaseSpawnerActor*> Spawners;

	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	float TimerTime;

	UPROPERTY(EditAnywhere, Category = "Teleport", meta = (AllowPrivateAccess = true))
	FVector TeleportLocation;

	UPROPERTY(EditAnywhere, Category = "Audio", meta = (AllowPrivateAccess = true))
	FString SoundName;

	FTimerHandle RemainTimer;

public:
	virtual void QuestClear();
	virtual void QuestFailed();

protected:
	virtual void SetUpTrigger() override;
	virtual void TearDownTrigger() override;

	virtual void SpawnMonster() {};
	virtual void DeSpawnMonster() {};

	virtual void SetReturnHome();

protected:
	void SetUpTimer(float const& Time);

	void AddRemoveWidget(FString const& WidgetName);
};
