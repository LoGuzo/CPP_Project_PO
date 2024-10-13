// Fill out your copyright notice in the Description page of Project Settings.


#include "BossHpMainWidget.h"
#include "BossHpWidget.h"

void UBossHpMainWidget::SetBossHp(UStatComponent* StatComponent)
{
	if (StatComponent)
		WBP_BossHp->BindHp(StatComponent);
}
