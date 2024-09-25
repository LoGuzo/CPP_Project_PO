// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/WidgetManager.h"
#include "../../Widget/HUD/MyHUDWidget.h"

ABasePlayerController::ABasePlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>MainHUD(TEXT("/Game/ThirdPerson/Blueprints/Widget/HUD/WBP_HUDWidget.WBP_HUDWidget_C"));
	if (MainHUD.Succeeded())
		HUDWidget = MainHUD.Class;
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetUpWidget();
}

void ABasePlayerController::SetUpWidget()
{
	auto MyGameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (MyGameInstance)
	{
		if (HUDWidget)
		{
			UWidgetManager* WidgetManager = MyGameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
			if (WidgetManager)
			{
				UMyHUDWidget* HUD = WidgetManager->CreateAndAddWidget<APlayerController, UMyHUDWidget>(this, TEXT("HUD"), HUDWidget);
				if (HUD)
					HUD->SetAddRemove();
			}
		}
	}
}