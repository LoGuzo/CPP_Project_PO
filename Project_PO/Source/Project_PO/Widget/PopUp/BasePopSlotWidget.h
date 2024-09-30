// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePopUpWidget.h"
#include "BasePopSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBasePopSlotWidget : public UBasePopUpWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Use;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Drop;

protected:
	int32 Index;
	int32 ItemID;
	class UInventoryComponent* InventoryComponent;

private:
	UFUNCTION()
	void DropItem();

public:
	void SetIndex(int32 _Index) { Index = _Index; }
	void SetItemID(int32 _ItemID) { ItemID = _ItemID; }
	void SetInventoryComponent(class UInventoryComponent* _InventoryComponent) { InventoryComponent = _InventoryComponent; }
};
