// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemActor.h"
#include "../../Interface/Interactable.h"
#include "DropItemActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ADropItemActor : public ABaseItemActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	ADropItemActor();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

public:
	virtual void Interact(class AActor* PlayerCharacter) override;

protected:
	virtual void SetMeshComponent(TSoftObjectPtr<UStreamableRenderAsset> Mesh) override;

	virtual void ResetItem() override;

private:
	void SetBoxComponent();
	void ResetMesh();
};
