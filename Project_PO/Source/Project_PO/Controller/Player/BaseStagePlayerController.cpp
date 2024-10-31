// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStagePlayerController.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/ObjectPoolManager.h"
#include "../../Manager/WidgetManager.h"
#include "../../Widget/Etc/TimerWidget.h"
#include "../../Widget/Etc/WeaponSelectWidget.h"
#include "../../Widget/PopUp/DamagePopUpWidget.h"
#include "../../Widget/HUD/MyHUDWidget.h"

ABaseStagePlayerController::ABaseStagePlayerController()
	: ClassType(E_ClassType::E_Boy)
{
	static ConstructorHelpers::FClassFinder<UUserWidget>MainHUD(TEXT("/Game/ThirdPerson/Blueprints/Widget/HUD/WBP_HUDWidget.WBP_HUDWidget_C"));
	if (MainHUD.Succeeded())
		HUDWidget = MainHUD.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>DamageWidget(TEXT("/Game/ThirdPerson/Blueprints/Widget/Popup/WBP_DamagePopUp.WBP_DamagePopUp_C"));
	if (DamageWidget.Succeeded())
		DamagePopUpWidget = DamageWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>WeaponSelect(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/WBP_WeaponSelect.WBP_WeaponSelect_C"));
	if (WeaponSelect.Succeeded())
		WeaponSelectWidget = WeaponSelect.Class;
}

void ABaseStagePlayerController::InitPlayerState()
{
	Super::InitPlayerState();
	SetupClassType();
}

void ABaseStagePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetUpWidget();
}

void ABaseStagePlayerController::SetUpWidget()
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
			}
		}
	}
}

void ABaseStagePlayerController::SequenceFinished()
{
	if (Sequence)
	{
		ShowHideWidget(TEXT("HUD"));
		Sequence->OnFinished.Clear();
		Sequence = nullptr;
	}
}

void ABaseStagePlayerController::SetupClassType()
{
	if (IsLocalController())
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
			SetClassType(GameInstance->GetClassType());
	}
}

void ABaseStagePlayerController::SetUpDamageWidget(E_DamageType const& Type, FVector const& Location, int32 const& Damage)
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

void ABaseStagePlayerController::SetUpTimerWidget(float const& RemainingTime)
{
	if (IsLocalController())
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
			if (WidgetManager)
			{
				UTimerWidget* NowWidget = WidgetManager->GetWidget<UTimerWidget>(TEXT("Timer"));
				if (NowWidget)
				{
					NowWidget->SetReminingTime(RemainingTime);

					if (!NowWidget->IsInViewport())
						NowWidget->AddToViewport();
				}
			}
		}
	}
}

void ABaseStagePlayerController::AddRemoveWidget(FString const& WidgetName)
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

void ABaseStagePlayerController::ShowHideWidget(FString const& WidgetName)
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

void ABaseStagePlayerController::PlaySequence(ULevelSequencePlayer* SequencePlayer)
{
	if (!Sequence)
	{
		Sequence = SequencePlayer;

		ShowHideWidget(TEXT("HUD"));
		Sequence->OnFinished.AddDynamic(this, &ABaseStagePlayerController::SequenceFinished);
		Sequence->Play();
	}
}

void ABaseStagePlayerController::SetUpWeaponSelectWidget()
{
	FTimerHandle WeaponTimer;
	GetWorld()->GetTimerManager().SetTimer(WeaponTimer, [this] {
		UWeaponSelectWidget* SelectWeapon = CreateWidget<UWeaponSelectWidget>(this, WeaponSelectWidget);
		if (SelectWeapon && !SelectWeapon->IsInViewport())
			SelectWeapon->AddToViewport();
		}, 2.f, false);
}