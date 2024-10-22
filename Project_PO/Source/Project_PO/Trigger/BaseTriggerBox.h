// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "../Interface/Teleportable.h"
#include "BaseTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABaseTriggerBox : public ATriggerBox, public ITeleportable
{
	GENERATED_BODY()
	
public:
	ABaseTriggerBox();
	
protected:
	virtual void Teleport() override;
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (AllowPrivateAccess = true))
	int32 ActiveCnt;

	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	TArray<class ABaseSpawnerActor*> Spawners;

	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	float TimerTime;
	
	UPROPERTY(EditAnywhere, Category = "Teleport", meta = (AllowPrivateAccess = true))
	FVector TeleportLocation;

	int32 CurActiveCnt;

	FTimerHandle RemainTimer;

protected:
	UFUNCTION()
	virtual void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	virtual void SetUpTrigger();
	virtual void SpawnMonster() {};
	virtual void DeSpawnMonster() {};
	virtual void TearDownTrigger();
	void SetUpTimer();

	void AddRemoveWidget(FString const& WidgetName);
};
