// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDestructableActor.generated.h"

UCLASS()
class PROJECT_PO_API ABaseDestructableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseDestructableActor();

protected:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	class UItemSpawnerComponent* ItemSpawnComponent;

	UPROPERTY()
	FTimerHandle DestroyTimerHandle;

private:
	bool bIsDestroy;

protected:
	UPROPERTY(EditAnywhere)
	class UGeometryCollectionComponent* GeometryCollectionComponent;

private:
	void SetUpBoxComponent();
	void SetUpGeometryComponent();
	void SetUpItemSpawnComponent();

	UFUNCTION()
	void DestroyObject();
};
