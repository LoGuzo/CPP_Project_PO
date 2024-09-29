// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHpInfoWidget.h"
#include "Components/ProgressBar.h"
#include "../../../Component/StatComponent/StatComponent.h"

void UBaseHpInfoWidget::BindHp(UStatComponent* _StatComp)
{
	if (_StatComp)
	{
		StatComponent = _StatComp;
		StatComponent->OnHpChanged.AddUObject(this, &UBaseHpInfoWidget::UpdateHp);
	}
}

void UBaseHpInfoWidget::UpdateHp()
{
	if (StatComponent)
		PB_Hp->SetPercent(StatComponent->GetHpRatio());
}