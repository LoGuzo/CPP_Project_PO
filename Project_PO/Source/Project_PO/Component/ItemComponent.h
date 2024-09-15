// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../MyEnumClass.h"
#include "ItemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PO_API UItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	int32 ItemID;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	FText ItemName;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	FText ItemDescription;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UTexture2D> ItemImage;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	int32 ItemStackSize;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	TEnumAsByte <E_ItemType> ItemType;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	int32 ItemAmount;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	float DropChance;

	UPROPERTY(EditAnywhere, Category = Item, Meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UStreamableRenderAsset> ItemMesh;

public:
	void SetItem(int32 _ItemID);
	TSoftObjectPtr<UStreamableRenderAsset> GetMesh() { return ItemMesh; }
};
