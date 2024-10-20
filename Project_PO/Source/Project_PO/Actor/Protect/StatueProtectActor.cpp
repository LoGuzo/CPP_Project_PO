// Fill out your copyright notice in the Description page of Project Settings.


#include "StatueProtectActor.h"
#include "../../Component/StatComponent/MonsterStatComponent.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/WidgetManager.h"
#include "../../Widget/InGame/CharInfo/BossHpMainWidget.h"

AStatueProtectActor::AStatueProtectActor()
{
	ActorID = 103;
}

void AStatueProtectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AStatueProtectActor::SetUpStatComponent()
{
	if (!StatComponent)
		return;

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UBossHpMainWidget* BossHp = WidgetManager->GetWidget<UBossHpMainWidget>(TEXT("BossHp"));
			if (BossHp)
				BossHp->SetBossHp(StatComponent);
		}
	}

	StatComponent->SetStat(ActorID);
}

void AStatueProtectActor::DelaySetUp()
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AStatueProtectActor::SetUpStatComponent, 2.f, false);
}
