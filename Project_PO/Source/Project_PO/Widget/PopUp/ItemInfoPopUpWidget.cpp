// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfoPopUpWidget.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../../Manager/BaseGameInstance.h"

void UItemInfoPopUpWidget::NativePreConstruct()
{
	if (ItemID != -1) {
		if (ItemType == E_ItemType::E_Equip)
			SetUpEquipInfo();
		else
			OtherInfo();
	}
}

void UItemInfoPopUpWidget::SetUpEquipInfo()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FEquipItemData>ItemData = GameInstance->GetDatabaseMap<FEquipItemData>(E_ManagerType::E_ItemDatabaseManager, ItemID);
		if (ItemData.IsValid())
		{
			UTexture2D* ItemImage = ItemData.Pin()->ItemImage.LoadSynchronous();
			if (Img_Item)
			{
				Img_Item->SetBrushFromTexture(ItemImage);
			}
			if (Txt_Name)
				Txt_Name->SetText(ItemData.Pin()->ItemName);

			if (Txt_Description)
				Txt_Description->SetText(ItemData.Pin()->ItemDescription);

			if (Txt_Attack)
				Txt_Attack->SetText(FText::FromString(FString::FromInt(ItemData.Pin()->AttackPower)));

			if (Txt_Armor)
				Txt_Armor->SetText(FText::FromString(FString::FromInt(ItemData.Pin()->DefensePower)));
		}
	}
}

void UItemInfoPopUpWidget::OtherInfo()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FItemData>ItemData = GameInstance->GetDatabaseMap<FItemData>(E_ManagerType::E_ItemDatabaseManager, ItemID);
		if (ItemData.IsValid())
		{
			UTexture2D* ItemImage = ItemData.Pin()->ItemImage.LoadSynchronous();
			if (Img_Item)
			{
				Img_Item->SetBrushFromTexture(ItemImage);
			}
			if (Txt_Name)
				Txt_Name->SetText(ItemData.Pin()->ItemName);

			if (Txt_Description)
				Txt_Description->SetText(ItemData.Pin()->ItemDescription);

			if (Border_Equip)
				Border_Equip->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
