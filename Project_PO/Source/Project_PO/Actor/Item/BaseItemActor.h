// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItemActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABaseItemActor : public AActor
{
	GENERATED_BODY()
	
public:
	ABaseItemActor();

private:
	UPROPERTY(VisibleAnywhere)
	class UItemComponent* ItemComponent;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere)
	class APlayerCharacter* OwnerCharacter;

protected:
	virtual void SetMeshComponent(TSoftObjectPtr<UStreamableRenderAsset> Mesh);

public:
	class UItemComponent* GetItemComponent() { return ItemComponent; }
	class UStaticMeshComponent* GetStaticMesh() { return StaticMesh; }
	class USkeletalMeshComponent* GetSkeletalMesh() { return SkeletalMesh; }

	void SetItem(int32 _ID);
	virtual void AfterDropItem();
};
