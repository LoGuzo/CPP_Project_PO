// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSlotWidget.h"
#include "../../../MyStructureAll.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UInventorySlotWidget : public UBaseSlotWidget
{
	GENERATED_BODY()

public:
	UInventorySlotWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

private:
	TSubclassOf<class UDragWidget> DragWidget;
	TSubclassOf<class UEquipPopSlotWidget> EquipPopSlotWidget;
	TSubclassOf<class UCunsumPopSlotWidget> CunsumPopSlotWidget;
	TSubclassOf<class UEtcPopSlotWidget> EtcPopSlotWidget;
	TSubclassOf<class UItemInfoPopUpWidget> ItemInfoWidget;

	class UDragDrop* DragDrop;

	class UInventoryComponent* InventoryComponent;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Slot;

private:
	int32 Amount;
	int32 ConIndex;
	FSpawnItemType Type;

private:
	void SetUpPopSlot(const FPointerEvent& InMouseEvent);
	void RemovePopSlot();

	void SetUpItemInfo(const FPointerEvent& InMouseEvent);
	void RemoveItemInfo();

public:
	void SetAmount(int32 const& _Amount) { Amount = _Amount; }
	void SetConIndex(int32 const& _ConIndex) { ConIndex = _ConIndex; }
	void SetType(FSpawnItemType const& _Type) { Type = _Type; }
	void SetInvetoryComponent(class UInventoryComponent* _InventoryComponent) { InventoryComponent = _InventoryComponent; }
};
