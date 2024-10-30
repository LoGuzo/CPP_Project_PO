// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/WidgetManager.h"
#include "../../Widget/Etc/SettingsWidget.h"

ABasePlayerController::ABasePlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>Settings(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/Settings/WBP_Settings.WBP_Settings_C"));
	if (Settings.Succeeded())
		SettingsWidget = Settings.Class;
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetUpSettingsWidget();
}

void ABasePlayerController::SetUpSettingsWidget()
{
	if (IsLocalController())
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
			if (WidgetManager)
			{
				if (SettingsWidget)
					WidgetManager->CreateAndAddWidget<ABasePlayerController, USettingsWidget>(this, TEXT("Settings"), SettingsWidget);
			}
		}
	}
}
