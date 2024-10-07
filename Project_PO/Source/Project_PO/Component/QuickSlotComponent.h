// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActorComponent.h"
#include "../MyStructureAll.h"
#include "QuickSlotComponent.generated.h"


UCLASS()
class PROJECT_PO_API UQuickSlotComponent : public UBaseActorComponent
{
	GENERATED_BODY()
	
public:
	UQuickSlotComponent();

protected:
	FSlot Slot;

public:
	virtual void RegisterQuickSlot(int32 const& _SlotIndex, UBaseActorComponent* ActorComponent) {};
	virtual void UseSlot() {};

public:
	FSlot GetSlot() { return Slot; }
};
