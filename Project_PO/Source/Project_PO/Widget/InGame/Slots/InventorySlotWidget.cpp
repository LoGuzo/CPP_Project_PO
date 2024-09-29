// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../../../Manager/BaseGameInstance.h"

void UInventorySlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		if (ID != -1) {
			TWeakPtr<FItemData>ItemData = GameInstance->GetDatabaseMap<FItemData>(E_ManagerType::E_ItemDatabaseManager, ID);
			if (ItemData.IsValid())
			{
				UTexture2D* ItemImage = ItemData.Pin()->ItemImage.LoadSynchronous();
				if (ItemData.Pin()->ItemType == E_ItemType::E_Equip)
				{
					Img_Slot->SetBrushFromTexture(ItemImage);
					Box_Slot->SetVisibility(ESlateVisibility::Hidden);
					Img_Slot->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					Img_Slot->SetBrushFromTexture(ItemImage);
					Box_Slot->SetVisibility(ESlateVisibility::Visible);
					Txt_Slot->SetText(FText::FromString(FString::FromInt(Amount)));
					Img_Slot->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
		else
		{
			Box_Slot->SetVisibility(ESlateVisibility::Hidden);
			Img_Slot->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UInventorySlotWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
