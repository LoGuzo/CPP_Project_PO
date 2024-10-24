// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpawnerActor.generated.h"

UCLASS()
class PROJECT_PO_API ABaseSpawnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSpawnerActor();

private:
	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	int32 SpawnMonsterID;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (AllowPrivateAccess = true))
	class UBoxComponent* SpawnArea;

	UPROPERTY(EditAnywhere, Category = "Target", meta = (AllowPrivateAccess = true))
	AActor* Target;

	UPROPERTY(EditAnywhere, Category = "Owner", meta = (AllowPrivateAccess = true))
	class ABaseSpawnTriggerBox* OwnerTrigger;

protected:
	TArray<class AEnemyCharacter*> SpawnEnemies;

public:
	void SpawnMonster();
	void DeSpawnMonster();

	void SetTarget(AActor* _Target) { Target = _Target; }
	void SetOwnerTrigger(class ABaseSpawnTriggerBox* _OwnerTrigger) { OwnerTrigger = _OwnerTrigger; }
};
