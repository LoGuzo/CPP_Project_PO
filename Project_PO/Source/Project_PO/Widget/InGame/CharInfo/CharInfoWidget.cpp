// Fill out your copyright notice in the Description page of Project Settings.


#include "CharInfoWidget.h"
#include "Components/ProgressBar.h"
#include "../../../Component/StatComponent/PlayerStatComponent.h"

void UCharInfoWidget::BindMp(UStatComponent* _StatComp)
{
	if (_StatComp)
	{
		StatComponent = _StatComp;
		StatComponent->OnMpChanged.AddUObject(this, &UCharInfoWidget::UpdateMp);
	}
}

void UCharInfoWidget::UpdateMp()
{
	if (StatComponent)
		PB_Mp->SetPercent(StatComponent->GetMpRatio());
}

void UCharInfoWidget::BindExp(UStatComponent* _StatComp)
{
	if (_StatComp)
	{
		StatComponent = _StatComp;

		UPlayerStatComponent* PlayerStatComponent = Cast<UPlayerStatComponent>(StatComponent);
		if(PlayerStatComponent)
			PlayerStatComponent->OnExpChanged.AddUObject(this, &UCharInfoWidget::UpdateExp);
	}
}

void UCharInfoWidget::UpdateExp()
{
	if (StatComponent)
	{
		UPlayerStatComponent* PlayerStatComponent = Cast<UPlayerStatComponent>(StatComponent);
		if (PlayerStatComponent)
			PB_Exp->SetPercent(PlayerStatComponent->GetExpRatio());
	}
}
