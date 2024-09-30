// Fill out your copyright notice in the Description page of Project Settings.


#include "DragWidget.h"
#include "Components/Image.h"
#include "../../../Manager/BaseGameInstance.h"

void UDragWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		if (ID != -1)
		{
			TWeakPtr<FItemData> ItemData = GameInstance->GetDatabaseMap<FItemData>(E_ManagerType::E_ItemDatabaseManager, ID);
			if (ItemData.IsValid())
			{
				UTexture2D* ItemImage = ItemData.Pin()->ItemImage.LoadSynchronous();

				if(Img_Drag)
					Img_Drag->SetBrushFromTexture(ItemImage);
			}
		}
	}
}