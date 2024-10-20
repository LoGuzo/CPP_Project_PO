// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/ObjectPoolManager.h"
#include "../../Manager/WidgetManager.h"
#include "../../Widget/InGame/CharInfo/BossHpMainWidget.h"
#include "../../Widget/InGame/Inventory/MainInventoryWidget.h"
#include "../../Widget/PopUp/DamagePopUpWidget.h"
#include "../../Widget/PopUp/AccessAlertWidget.h"
#include "../../Widget/HUD/MyHUDWidget.h"

ABasePlayerController::ABasePlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>MainHUD(TEXT("/Game/ThirdPerson/Blueprints/Widget/HUD/WBP_HUDWidget.WBP_HUDWidget_C"));
	if (MainHUD.Succeeded())
		HUDWidget = MainHUD.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>Inventory(TEXT("/Game/ThirdPerson/Blueprints/Widget/InGame/Inventory/WBP_MainInventory.WBP_MainInventory_C"));
	if (Inventory.Succeeded())
		InventoryWidget = Inventory.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>DamageWidget(TEXT("/Game/ThirdPerson/Blueprints/Widget/Popup/WBP_DamagePopUp.WBP_DamagePopUp_C"));
	if (DamageWidget.Succeeded())
		DamagePopUpWidget = DamageWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>AlertWidget(TEXT("/Game/ThirdPerson/Blueprints/Widget/Popup/Alert/WBP_AccessAlertWidget.WBP_AccessAlertWidget_C"));
	if (AlertWidget.Succeeded())
		AccessAlertWidget = AlertWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>BossHpWidget(TEXT("/Game/ThirdPerson/Blueprints/Widget/InGame/CharInfo/WBP_BossHpMain.WBP_BossHpMain_C"));
	if (BossHpWidget.Succeeded())
		BossHpMainWidget = BossHpWidget.Class;
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetUpWidget();
}

void ABasePlayerController::SetUpWidget()
{
	if (IsLocalController())
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
			if (WidgetManager)
			{
				if (HUDWidget)
				{
					UMyHUDWidget* HUD = WidgetManager->CreateAndAddWidget<APlayerController, UMyHUDWidget>(this, TEXT("HUD"), HUDWidget);
					if (HUD)
						HUD->SetAddRemove();
				}

				if (InventoryWidget)
					WidgetManager->CreateAndAddWidget<APlayerController, UMainInventoryWidget>(this, TEXT("Inven"), InventoryWidget);

				if (AccessAlertWidget)
					WidgetManager->CreateAndAddWidget<APlayerController, UAccessAlertWidget>(this, TEXT("Alert"), AccessAlertWidget);

				if (BossHpMainWidget)
					WidgetManager->CreateAndAddWidget<APlayerController, UBossHpMainWidget>(this, TEXT("BossHp"), BossHpMainWidget);
			}
		}
	}
}

void ABasePlayerController::SetUpDamageWidget(E_DamageType const& Type, FVector const& Location, int32 const& Damage)
{
	if (IsLocalController())
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{

			UObjectPoolManager* ObjectPoolManager = GameInstance->GetManager<UObjectPoolManager>(E_ManagerType::E_ObjectPoolManager);
			if (ObjectPoolManager)
			{
				FVector2D ScreenPosition;

				UGameplayStatics::ProjectWorldToScreen(this, Location, ScreenPosition);
				ObjectPoolManager->GetWidget(GetWorld(), Type, DamagePopUpWidget, ScreenPosition, Damage);
			}
		}
	}
}

void ABasePlayerController::AddRemoveWidget(FString const& WidgetName)
{
	if (IsLocalController())
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
			if (WidgetManager)
			{
				UBaseUserWidget* NowWidget = WidgetManager->GetWidget<UBaseUserWidget>(WidgetName);
				if (NowWidget)
					NowWidget->SetAddRemove();
			}
		}
	}
}

void ABasePlayerController::ShowHideWidget(FString const& WidgetName)
{
	if (IsLocalController())
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
			if (WidgetManager)
			{
				UBaseUserWidget* NowWidget = WidgetManager->GetWidget<UBaseUserWidget>(WidgetName);
				if (NowWidget)
					NowWidget->SetShowHidden();
			}
		}
	}
}