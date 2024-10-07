// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUDWidget.h"
#include "../../Character/BaseCharacter.h"
#include "../../Widget/InGame/CharInfo/CharInfoWidget.h"
#include "../../Widget/InGame/Slots/CunsumQuickSlotWidget.h"
#include "../../Widget/InGame/Slots/SkillQuickSlotWidget.h"
#include "../../Widget/InGame/Slots/WeaponSlotWidget.h"

UMyHUDWidget::UMyHUDWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
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