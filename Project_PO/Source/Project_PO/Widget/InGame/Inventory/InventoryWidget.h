// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseInGameWidget.h"
#include "../../../MyStructureAll.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UInventoryWidget : public UBaseInGameWidget
{
	GENERATED_BODY()
	
public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Equip;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Cunsum;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Etc;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* Wrap_Item;

	class UInventoryComponent* InventoryComponent;

	TSubclassOf<class UInventorySlotWidget> SlotWidget;

private:
	void UpdateSlots(const TArray<FSlot>& Slots);

	UFUNCTION()
	void EquipInven();
	UFUNCTION()
	void CunsumInven();
	UFUNCTION()
	void EtcInven();

public:
	void UpdateInventory(class UInventoryComponent* _InventoryComponent);
	void UpdateInventoryDrop();
};
