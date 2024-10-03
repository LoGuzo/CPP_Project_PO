// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../Inventory/DragWidget.h"
#include "../Inventory/InventoryWidget.h"
#include "../../PopUp/BasePopSlotWidget.h"
#include "../../PopUp/CunsumPopSlotWidget.h"
#include "../../PopUp/EquipPopSlotWidget.h"
#include "../../PopUp/EtcPopSlotWidget.h"
#include "../../PopUp/ItemInfoPopUpWidget.h"
#include "../../../Component/InventoryComponent.h"
#include "../../../DragDrop.h"
#include "../../../Manager/BaseGameInstance.h"
#include "../../../Manager/WidgetManager.h"

UInventorySlotWidget::UInventorySlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget>Drag(TEXT("/Game/ThirdPerson/Blueprints/Widget/InGame/Slots/WBP_Drag.WBP_Drag_C"));
	if (Drag.Succeeded())
		DragWidget = Drag.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>EquipPopSlot(TEXT("/Game/ThirdPerson/Blueprints/Widget/Popup/WBP_EquipPopSlot.WBP_EquipPopSlot_C"));
	if (EquipPopSlot.Succeeded())
		EquipPopSlotWidget = EquipPopSlot.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>CunsumPopSlot(TEXT("/Game/ThirdPerson/Blueprints/Widget/Popup/WBP_CunsumPopSlot.WBP_CunsumPopSlot_C"));
	if (CunsumPopSlot.Succeeded())
		CunsumPopSlotWidget = CunsumPopSlot.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>EtcPopSlot(TEXT("/Game/ThirdPerson/Blueprints/Widget/Popup/WBP_EtcPopSlot.WBP_EtcPopSlot_C"));
	if (EtcPopSlot.Succeeded())
		EtcPopSlotWidget = EtcPopSlot.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>ItemInfo(TEXT("/Game/ThirdPerson/Blueprints/Widget/Popup/WBP_PopUpItemInfo.WBP_PopUpItemInfo_C"));
	if (ItemInfo.Succeeded())
		ItemInfoWidget = ItemInfo.Class;
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
	RemovePopSlot();
	RemoveItemInfo();
}

FReply UInventorySlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	RemovePopSlot();

	if (ID == -1)
		return FReply::Unhandled();


	FEventReply reply;
	reply.NativeReply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		SetUpPopSlot(InMouseEvent);
		return FReply::Handled();
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

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (ID == -1)
		return;

	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	SetUpItemInfo(InMouseEvent);
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	RemoveItemInfo();
}

void UInventorySlotWidget::SetUpPopSlot(const FPointerEvent& InMouseEvent)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UBasePopSlotWidget* PopSlotWidget = nullptr;

			switch (Type.ItemType)
			{
			case E_ItemType::E_Equip:
				if (EquipPopSlotWidget)
					PopSlotWidget = Cast<UBasePopSlotWidget>(WidgetManager
						->CreateAndAddWidget<UInventorySlotWidget, UEquipPopSlotWidget>(
							this, TEXT("PopUpSlot"), EquipPopSlotWidget
						));
				break;
			case E_ItemType::E_Cunsumable:
				if (CunsumPopSlotWidget)
					PopSlotWidget = Cast<UBasePopSlotWidget>(WidgetManager
						->CreateAndAddWidget<UInventorySlotWidget, UCunsumPopSlotWidget>(
							this, TEXT("PopUpSlot"), CunsumPopSlotWidget
						));
				break;
			case E_ItemType::E_Etc:
				if (EtcPopSlotWidget)
					PopSlotWidget = Cast<UBasePopSlotWidget>(WidgetManager
						->CreateAndAddWidget<UInventorySlotWidget, UEtcPopSlotWidget>(
							this, TEXT("PopUpSlot"), EtcPopSlotWidget
						));
				break;
			default:
				break;
			}

			if (PopSlotWidget)
			{
				PopSlotWidget->SetItemID(ID);
				PopSlotWidget->SetIndex(ConIndex);
				PopSlotWidget->SetType(Type);
				PopSlotWidget->SetInventoryComponent(InventoryComponent);
				FVector2D MousePosition = InMouseEvent.GetScreenSpacePosition();
				FVector2D ViewportPosition = UWidgetLayoutLibrary::GetViewportWidgetGeometry(this).AbsoluteToLocal(MousePosition);
				PopSlotWidget->SetPositionInViewport(ViewportPosition, false);
				PopSlotWidget->SetAddRemove();
			}
		}
	}
}

void UInventorySlotWidget::RemovePopSlot()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UBasePopSlotWidget* PopSlotWidget = WidgetManager->GetWidget<UBasePopSlotWidget>(TEXT("PopUpSlot"));
			if (PopSlotWidget)
				if (PopSlotWidget->IsInViewport())
					PopSlotWidget->RemoveFromParent();
		}
	}
}

void UInventorySlotWidget::SetUpItemInfo(const FPointerEvent& InMouseEvent)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UItemInfoPopUpWidget* ItemInfoPopUp = WidgetManager
				->CreateAndAddWidget<UInventorySlotWidget, UItemInfoPopUpWidget>(
					this, TEXT("ItemInfo"), ItemInfoWidget
				);
			if (ItemInfoPopUp)
			{
				ItemInfoPopUp->SetItemID(ID);
				ItemInfoPopUp->SetItemType(Type.ItemType);
				FVector2D MousePosition = InMouseEvent.GetScreenSpacePosition();
				FVector2D ViewportPosition = UWidgetLayoutLibrary::GetViewportWidgetGeometry(this).AbsoluteToLocal(MousePosition);
				ItemInfoPopUp->SetPositionInViewport(ViewportPosition, false);
				ItemInfoPopUp->SetAddRemove();
			}
		}
	}
}

void UInventorySlotWidget::RemoveItemInfo()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UItemInfoPopUpWidget* ItemInfoPopUp = WidgetManager->GetWidget<UItemInfoPopUpWidget>(TEXT("ItemInfo"));
			if (ItemInfoPopUp)
				ItemInfoPopUp->RemoveFromParent();
		}
	}
}
