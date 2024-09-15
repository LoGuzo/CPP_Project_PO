// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "../Interface/Interactable.h"
#include "OwlTeleportActor.generated.h"

UCLASS()
class PROJECT_PO_API AOwlTeleportActor : public AInteractActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOwlTeleportActor();

private:
	UPROPERTY()
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Teleport, meta = (AllowPrivateAccess = "true"))
	FVector TeleportLocation;

private:
	void SetBoxComponent();
	void SetActorMesh();


public:
	virtual void Interact(class AActor* PlayerCharacter) override;

	class UStaticMeshComponent* GetMesh() { return Mesh; }
};
