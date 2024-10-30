// Fill out your copyright notice in the Description page of Project Settings.


#include "StartPlayerController.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/WidgetManager.h"
#include "../../Widget/HUD/StartHUDWidget.h"

AStartPlayerController::AStartPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>StartHUD(TEXT("/Game/ThirdPerson/Blueprints/Widget/HUD/WBP_StartHUDWidget.WBP_StartHUDWidget_C"));
	if (StartHUD.Succeeded())
		StartHUDWidget = StartHUD.Class;
}

void AStartPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetUpWidget();
}

void AStartPlayerController::SetUpWidget()
{
	if (IsLocalController())
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
			if (WidgetManager)
			{
				if (StartHUDWidget)
				{
					UStartHUDWidget* StartHUD =  WidgetManager->CreateAndAddWidget<AStartPlayerController, UStartHUDWidget>(this, TEXT("StartHUD"), StartHUDWidget);
					if (StartHUD)
						StartHUD->SetAddRemove();
				}
			}
		}
	}
}
