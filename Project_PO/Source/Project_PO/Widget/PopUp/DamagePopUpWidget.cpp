// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagePopUpWidget.h"
#include "Components/TextBlock.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/ObjectPoolManager.h"

void UDamagePopUpWidget::ReleaseTimer()
{
	GetWorld()->GetTimerManager().SetTimer(ReleaseTimerHandle, this, &UDamagePopUpWidget::Release, 2.f, false);
}

void UDamagePopUpWidget::SetDamageText(int32 const& Damage)
{
	if(Txt_Damage)
		Txt_Damage->SetText(FText::FromString(FString::FromInt(Damage)));

	if (DamageAnim)
	{
		PlayAnimation(DamageAnim);
		ReleaseTimer();
	}
}

void UDamagePopUpWidget::SetCriticalText(int32 const& Damage)
{
	if (Txt_Damage)
		Txt_Damage->SetText(FText::FromString(FString::FromInt(Damage)));

	if (CriticalAnim)
	{
		PlayAnimation(CriticalAnim);
		ReleaseTimer();
	}
}

void UDamagePopUpWidget::Release()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UObjectPoolManager* ObjectPoolManager = GameInstance->GetManager<UObjectPoolManager>(E_ManagerType::E_ObjectPoolManager);
		if (ObjectPoolManager)
			ObjectPoolManager->ReleaseWidget(this);
	}
}