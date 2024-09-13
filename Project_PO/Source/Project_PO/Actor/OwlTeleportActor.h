// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "OwlTeleportActor.generated.h"

UCLASS()
class PROJECT_PO_API AOwlTeleportActor : public AInteractActor
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
	void SetWidgetComponent();

public:
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	class UStaticMeshComponent* GetMesh() { return Mesh; }
};
