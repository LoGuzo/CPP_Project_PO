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
	class UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;

protected:
	UPROPERTY(VisibleAnywhere)
	class UItemComponent* ItemComponent;

protected:
	virtual void SetMeshComponent(TSoftObjectPtr<UStreamableRenderAsset> Mesh);

public:
	template<typename T>
	T* GetItemComponent()
	{
		return Cast<T>(ItemComponent);
	}

	class UStaticMeshComponent* GetStaticMesh() { return StaticMesh; }
	class USkeletalMeshComponent* GetSkeletalMesh() { return SkeletalMesh; }

	virtual void SetItem(int32 _ID);
	virtual void AfterDropItem();
};
