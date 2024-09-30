// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../Inventory/DragWidget.h"
#include "../../../Component/InventoryComponent.h"
#include "../../../DragDrop.h"
#include "../../../Manager/BaseGameInstance.h"

UInventorySlotWidget::UInventorySlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UDragWidget>Drag(TEXT("/Game/ThirdPerson/Blueprints/Widget/InGame/Slots/WBP_Drag.WBP_Drag_C"));
	if (Drag.Succeeded())
		DragWidget = Drag.Class;
}

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
				if (Img_Slot)
				{
					Img_Slot->SetBrushFromTexture(ItemImage);
					Img_Slot->SetVisibility(ESlateVisibility::Visible);
				}

				if(Box_Slot)
					Box_Slot->SetVisibility(ESlateVisibility::Visible);

				if (ItemData.Pin()->ItemType.ItemType == E_ItemType::E_Equip)
					if(Txt_Slot)
						Txt_Slot->SetVisibility(ESlateVisibility::Hidden);
				else
					if (Txt_Slot)
						Txt_Slot->SetText(FText::FromString(FString::FromInt(Amount)));
			}
		}
		else
		{
			if (Box_Slot)
				Box_Slot->SetVisibility(ESlateVisibility::Hidden);

			if (Img_Slot)
				Img_Slot->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UInventorySlotWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply UInventorySlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		return reply.NativeReply;
	}
	return FReply::Unhandled();
}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	DragDrop = Cast<UDragDrop>(InOperation);

	if (DragDrop)
	{
		if (DragDrop->GetIndex() != ConIndex || DragDrop->GetInvenComponent() != InventoryComponent)
		{
			if (InventoryComponent)
				InventoryComponent->ChangeSlot(DragDrop->GetIndex(), ConIndex, InventoryComponent);
		}
	}

	return false;
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (OutOperation == nullptr)
	{
		if (DragWidget)
		{
			UDragWidget* DragImg = CreateWidget<UDragWidget>(this, DragWidget);
			if (DragImg)
			{
				if (ID != -1)
					DragImg->SetID(ID);
			}

			DragDrop = NewObject<UDragDrop>();
			OutOperation = DragDrop;
			if (DragDrop)
			{
				DragDrop->SetID(ID);
				DragDrop->SetIndex(ConIndex);
				DragDrop->SetItemType(Type.ItemType);
				if (InventoryComponent)
					DragDrop->SetInvenComponent(InventoryComponent);
				DragDrop->DefaultDragVisual = DragImg;
			}
		}
	}
}
