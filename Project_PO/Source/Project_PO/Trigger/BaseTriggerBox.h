// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "BaseTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABaseTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	ABaseTriggerBox();
	
protected:
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (AllowPrivateAccess = true))
	int32 ActiveCnt;

	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	TArray<class ABaseSpawnerActor*> Spawners;

	int32 CurActiveCnt;

protected:
	virtual void SetUpTrigger();
	virtual void SpawnMonster() {};
};
