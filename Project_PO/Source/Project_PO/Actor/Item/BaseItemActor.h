// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../MyEnumClass.h"
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

protected:
	virtual void BeginPlay() override;

protected:
	virtual void SetMeshComponent(TSoftObjectPtr<UStreamableRenderAsset> Mesh);

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;

protected:
	UPROPERTY(VisibleAnywhere)
	class UItemComponent* ItemComponent;

	E_ItemType ItemType;
	E_EquipType EquipType;

public:
	template<typename T>
	T* GetItemComponent()
	{
		return Cast<T>(ItemComponent);
	}

	class UStaticMeshComponent* GetStaticMesh() { return StaticMesh; }
	class USkeletalMeshComponent* GetSkeletalMesh() { return SkeletalMesh; }

	UFUNCTION(BlueprintCallable)
	virtual void SetItem(int32 _ID);
	virtual void ResetItem();
	void SetState(bool NowState);

	E_EquipType GetEquipType() { return EquipType; }
	E_ItemType GetItemType() { return ItemType; }
};
