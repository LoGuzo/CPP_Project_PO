// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuickSlotComponent.h"
#include "PotionQuickSlotComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnQuickSlotUpdated);

UCLASS()
class PROJECT_PO_API UPotionQuickSlotComponent : public UQuickSlotComponent
{
	GENERATED_BODY()

public:
	UPotionQuickSlotComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UInventoryComponent* InventoryComponent;

	class ABaseItemActor* CurItem;

private:
	int32 SlotIndex;

public:
	FOnQuickSlotUpdated OnQuickSlotUpdated;

public:
	virtual void RegisterQuickSlot(int32 const& _SlotIndex, UBaseActorComponent* ActorComponent) override;
	virtual void UseSlot() override;

public:
	void SetInventoryComponent(class UInventoryComponent* _InventoryComponent) { InventoryComponent = _InventoryComponent; }

	void SetupQuickSlotWidget();
	void UpdateQuickSlotWidget();
	void UpdateQuickSlotAmount();

	void SetUpQuickItem();
};
