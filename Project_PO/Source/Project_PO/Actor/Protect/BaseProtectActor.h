// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProtectActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDestruct);

UCLASS()
class PROJECT_PO_API ABaseProtectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProtectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	FOnDestruct OnDestruct;

protected:
	UPROPERTY()
	class UMonsterStatComponent* StatComponent;

	int32 ActorID;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleCollision;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

protected:
	bool bIsDied;

public:
	void SetState(bool NowState);

	int32 GetActorID() { return ActorID; }
};
