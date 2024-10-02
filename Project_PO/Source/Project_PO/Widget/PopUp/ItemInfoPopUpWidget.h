// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePopUpWidget.h"
#include "ItemInfoPopUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UItemInfoPopUpWidget : public UBasePopUpWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Description;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Item;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_Equip;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Attack;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Armor;

private:
	int32 ItemID;

	E_ItemType ItemType;

private:
	void SetUpEquipInfo();
	void OtherInfo();

public:
	void SetItemID(int32 _ItemID) { ItemID = _ItemID; }
	
	void SetItemType(E_ItemType _ItemType) { ItemType = _ItemType; }
};
