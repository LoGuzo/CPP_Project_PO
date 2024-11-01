// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "../../../Widget/PopUp/PopGameExitWidget.h"
#include "../../../Manager/BaseGameInstance.h"
#include "../../../Manager/WidgetManager.h"

UMenuWidget::UMenuWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget>PopGameExit(TEXT("/Game/ThirdPerson/Blueprints/Widget/Popup/WBP_PopGameExit.WBP_PopGameExit_C"));
	if (PopGameExit.Succeeded())
		PopGameExitWidget = PopGameExit.Class;
}

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Settings)
		Btn_Settings->OnClicked.AddDynamic(this, &UMenuWidget::ClickedSettingsBtn);

	if (Btn_Inven)
		Btn_Inven->OnClicked.AddDynamic(this, &UMenuWidget::ClickedInvenBtn);

	if (Btn_Exit)
		Btn_Exit->OnClicked.AddDynamic(this, &UMenuWidget::ClickedExitBtn);
}

void UMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (Btn_Settings)
		Btn_Settings->OnClicked.RemoveDynamic(this, &UMenuWidget::ClickedSettingsBtn);

	if (Btn_Inven)
		Btn_Inven->OnClicked.RemoveDynamic(this, &UMenuWidget::ClickedInvenBtn);

	if (Btn_Exit)
		Btn_Exit->OnClicked.RemoveDynamic(this, &UMenuWidget::ClickedExitBtn);
}

void UMenuWidget::ClickedSettingsBtn()
{
	SetAddRemoveWidget(TEXT("Settings"));
}

void UMenuWidget::ClickedInvenBtn()
{
	SetAddRemoveWidget(TEXT("Inven"));
}

void UMenuWidget::ClickedExitBtn()
{
	UPopGameExitWidget* Widget = CreateWidget<UPopGameExitWidget>(this, PopGameExitWidget);
	if (Widget)
		Widget->SetAddRemove();
}

void UMenuWidget::SetAddRemoveWidget(FString const& Name)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UBaseUserWidget* Widget = WidgetManager->GetWidget<UBaseUserWidget>(Name);
			if (Widget)
				Widget->SetAddRemove();
		}
	}
}
