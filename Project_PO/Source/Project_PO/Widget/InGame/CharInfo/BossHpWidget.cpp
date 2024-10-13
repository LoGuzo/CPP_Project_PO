// Fill out your copyright notice in the Description page of Project Settings.


#include "BossHpWidget.h"
#include "Components/TextBlock.h"
#include "../../../Component/StatComponent/MonsterStatComponent.h"

void UBossHpWidget::BindHp(UStatComponent* _StatComp)
{
	if (_StatComp)
	{
		StatComponent = _StatComp;
		StatComponent->OnHpChanged.AddUObject(this, &UBossHpWidget::UpdateHp);
	}
}

void UBossHpWidget::UpdateHp()
{
	Super::UpdateHp();

	if (StatComponent)
	{
		UMonsterStatComponent* MonsterStatComponent = Cast<UMonsterStatComponent>(StatComponent);
		if (MonsterStatComponent)
		{
			if (Txt_Hp)
			{
				int32 Hp = MonsterStatComponent->GetHp();
				int32 MaxHp = MonsterStatComponent->GetMaxHp();
				Txt_Hp->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), Hp, MaxHp)));
			}
			if (Txt_HpPer)
			{
				int32  HpPer = MonsterStatComponent->GetHpRatio() * 100;
				Txt_HpPer->SetText(FText::FromString(FString::Printf(TEXT("%d%"), HpPer)));
			}
			if (Txt_Name)
			{
				FString string = MonsterStatComponent->GetMonsterName().ToString();
				if (Txt_Name->GetText().ToString() != string)
				{
					FText MonsterName = FText::FromString(string);
					Txt_Name->SetText(MonsterName);
				}
			}
		}
	}
}