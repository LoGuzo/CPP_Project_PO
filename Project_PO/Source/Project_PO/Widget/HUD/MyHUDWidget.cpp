// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUDWidget.h"
#include "../../Character/BaseCharacter.h"
#include "../../Widget/InGame/CharInfo/CharInfoWidget.h"
#include <Kismet/GameplayStatics.h>

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