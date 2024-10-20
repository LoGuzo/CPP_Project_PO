// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSpawnerActor.h"
#include "InfiniteSpawnerActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AInfiniteSpawnerActor : public ABaseSpawnerActor
{
	GENERATED_BODY()
	
public:
	AInfiniteSpawnerActor();

protected:
	virtual void Tick(float DeltaSeconds) override;

private:
	bool bIsSpawn;

protected:
	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	float SpawnInterval;

	float TimeSinceLastSpawn;

public:
	void SetIsSpawn(bool const& _bIsSpawn) { bIsSpawn = _bIsSpawn; }
	bool GetIsSpawn() { return bIsSpawn; }
};
