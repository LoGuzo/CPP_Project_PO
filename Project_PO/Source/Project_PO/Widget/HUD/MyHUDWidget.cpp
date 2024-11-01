// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUDWidget.h"
#include "../../Character/BaseCharacter.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/WidgetManager.h"
#include "../../Widget/Etc/TimerWidget.h"
#include "../../Widget/Etc/QuestClearWidget.h"
#include "../../Widget/Etc/RespawnWidget.h"
#include "../../Widget/PopUp/AccessAlertWidget.h"
#include "../../Widget/InGame/CharInfo/BossHpMainWidget.h"
#include "../../Widget/InGame/CharInfo/CharInfoWidget.h"
#include "../../Widget/InGame/Menu/MenuMainWidget.h"
#include "../../Widget/InGame/Inventory/MainInventoryWidget.h"
#include "../../Widget/InGame/Slots/CunsumQuickSlotWidget.h"
#include "../../Widget/InGame/Slots/SkillQuickSlotWidget.h"
#include "../../Widget/InGame/Slots/WeaponSlotWidget.h"
#include "../../Widget/InGame/Quest/QuestMainWidget.h"

UMyHUDWidget::UMyHUDWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget>Inventory(TEXT("/Game/ThirdPerson/Blueprints/Widget/InGame/Inventory/WBP_MainInventory.WBP_MainInventory_C"));
	if (Inventory.Succeeded())
		InventoryWidget = Inventory.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>AlertWidget(TEXT("/Game/ThirdPerson/Blueprints/Widget/Popup/Alert/WBP_AccessAlertWidget.WBP_AccessAlertWidget_C"));
	if (AlertWidget.Succeeded())
		AccessAlertWidget = AlertWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>BossHpWidget(TEXT("/Game/ThirdPerson/Blueprints/Widget/InGame/CharInfo/WBP_BossHpMain.WBP_BossHpMain_C"));
	if (BossHpWidget.Succeeded())
		BossHpMainWidget = BossHpWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>Timer(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/WBP_Timer.WBP_Timer_C"));
	if (Timer.Succeeded())
		TimerWidget = Timer.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>QuestClear(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/WBP_QuestClear.WBP_QuestClear_C"));
	if (QuestClear.Succeeded())
		QuestClearWidget = QuestClear.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>Respawn(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/WBP_RespawnWidget.WBP_RespawnWidget_C"));
	if (Respawn.Succeeded())
		RespawnWidget = Respawn.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>MenuMain(TEXT("/Game/ThirdPerson/Blueprints/Widget/InGame/Menu/WBP_MenuMain.WBP_MenuMain_C"));
	if (MenuMain.Succeeded())
		MenuMainWidget = MenuMain.Class;
}

void UMyHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetUpWidget();
}

void UMyHUDWidget::SetUpWidget()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			if (InventoryWidget)
				WidgetManager->CreateAndAddWidget<UMyHUDWidget, UMainInventoryWidget>(this, TEXT("Inven"), InventoryWidget);

			if (AccessAlertWidget)
				WidgetManager->CreateAndAddWidget<UMyHUDWidget, UAccessAlertWidget>(this, TEXT("Alert"), AccessAlertWidget);

			if (BossHpMainWidget)
				WidgetManager->CreateAndAddWidget<UMyHUDWidget, UBossHpMainWidget>(this, TEXT("BossHp"), BossHpMainWidget);

			if (TimerWidget)
				WidgetManager->CreateAndAddWidget<UMyHUDWidget, UTimerWidget>(this, TEXT("Timer"), TimerWidget);

			if (QuestClearWidget)
				WidgetManager->CreateAndAddWidget<UMyHUDWidget, UQuestClearWidget>(this, TEXT("QuestClear"), QuestClearWidget);

			if (RespawnWidget)
				WidgetManager->CreateAndAddWidget<UMyHUDWidget, URespawnWidget>(this, TEXT("Respawn"), RespawnWidget);

			if (MenuMainWidget)
				WidgetManager->CreateAndAddWidget<UMyHUDWidget, UMenuMainWidget>(this, TEXT("Menu"), MenuMainWidget);
		}
	}
}

void UMyHUDWidget::SetUpCharInfo(UStatComponent* StatComponent)
{
	if (!StatComponent)
		return;

	if (WBP_CharInfo)
	{
		WBP_CharInfo->BindHp(StatComponent);
		WBP_CharInfo->BindMp(StatComponent);
		WBP_CharInfo->BindExp(StatComponent);
	}
}

void UMyHUDWidget::SetUpCunsumQuickSlot(UPotionQuickSlotComponent* PotionQuickSlotComponent)
{
	if (!PotionQuickSlotComponent)
		return;

	if (WBP_CunsumQuickSlot)
	{
		WBP_CunsumQuickSlot->SetTextKey(TEXT("1"));
		WBP_CunsumQuickSlot->BindText(PotionQuickSlotComponent);
	}
}

void UMyHUDWidget::SetUpWeaponSlot(int32 const& ID)
{
	WBP_WeaponSlot->SetUpWidget(ID);
}

void UMyHUDWidget::SetUpQuestMain(int32 const& ID)
{
	WBP_QuestMain->SetUpWidget(ID);
}