// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "../../Interface/Interactable.h"
#include "../../Interface/Teleportable.h"
#include "OwlTeleportActor.generated.h"

UCLASS()
class PROJECT_PO_API AOwlTeleportActor : public AInteractActor, public IInteractable, public ITeleportable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOwlTeleportActor();

public:
	virtual void Interact(class AActor* PlayerCharacter) override;

private:
	UFUNCTION()
	virtual void Teleport() override;

private:
	UPROPERTY()
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Teleport, meta = (AllowPrivateAccess = "true"))
	FVector TeleportLocation;

public:
	class UStaticMeshComponent* GetMesh() { return Mesh; }

private:
	void SetBoxComponent();
	void SetActorMesh();
	void SetLevelSequence();
};
