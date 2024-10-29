// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "../../../Manager/BaseGameInstance.h"
#include "../../../Manager/WidgetManager.h"

void UQuestItemWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ID != -1) {
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
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

				if (ItemData.Pin()->ItemType.ItemType == E_ItemType::E_Equip)
				{
					if (Txt_Slot)
						Txt_Slot->SetVisibility(ESlateVisibility::Hidden);
				}
				else
				{
					if (Txt_Slot)
						Txt_Slot->SetText(FText::FromString(FString::FromInt(Amount)));
				}
			}
		}
	}

}
