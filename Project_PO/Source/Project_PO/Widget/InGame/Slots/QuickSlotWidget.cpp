// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotWidget.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../../../Manager/BaseGameInstance.h"

void UQuickSlotWidget::SetUpWidget(int32 const& _ID)
{
	ID = _ID;
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		if (ID != -1) {
			TWeakPtr<FItemData>ItemData = GameInstance->GetDatabaseMap<FItemData>(E_ManagerType::E_ItemDatabaseManager, ID);
			if (ItemData.IsValid())
			{
				UTexture2D* ItemImage = ItemData.Pin()->ItemImage.LoadSynchronous();
				if (Img_Slot)
				{
					Img_Slot->SetBrushFromTexture(ItemImage);
					Img_Slot->SetVisibility(ESlateVisibility::Visible);
				}

				if (Box_Slot)
					Box_Slot->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			if (Box_Slot)
				Box_Slot->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UQuickSlotWidget::SetTextKey(FString const& Key)
{
	if (Txt_Key)
		Txt_Key->SetText(FText::FromString(Key));
}
