// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "MyEnumClass.h"
#include "DragDrop.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UDragDrop : public UDragDropOperation
{
	GENERATED_BODY()

private:
	int32 ID;
	E_ItemType ItemType;
	int32 Index;

	class UInventoryComponent* InventoryComponent;

public:
	int32 GetID() { return ID; }
	void SetID(int32 const& _ID) { ID = _ID; }

	E_ItemType GetItemType() { return ItemType; }
	void SetItemType(E_ItemType const& _ItemType) { ItemType = _ItemType; }

	int32 GetIndex() { return Index; }
	void SetIndex(int32 const& _Index) { Index = _Index; }

	class UInventoryComponent* GetInvenComponent() { return InventoryComponent; }
	void SetInvenComponent(class UInventoryComponent* _InventoryComponent) { InventoryComponent = _InventoryComponent; }
};
