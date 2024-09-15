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

	void SetState(bool NowState);

	virtual void AfterDropItem() override;
private:
	void SetBoxComponent();
	void SetMeshComponent(TSoftObjectPtr<UStreamableRenderAsset> Mesh);
};
