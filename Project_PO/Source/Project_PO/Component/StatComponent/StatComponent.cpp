// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "../../Character/BaseCharacter.h"
#include "../../Manager/DatabaseManager/ClassDatabaseManager.h"

UStatComponent::UStatComponent()
{
}

void UStatComponent::SetStat(int32 const& _ID)
{
}

void UStatComponent::TakeDamage(float const& TakedDamage)
{
	if (Hp == 0)
		return;

	float CurHp = Hp;
	CurHp -= TakedDamage;

	if (CurHp <= 0)
	{
		CurHp = 0;
		ABaseCharacter* OwnCharacter = Cast<ABaseCharacter>(GetOwner());
		if (OwnCharacter)
			if (!OwnCharacter->GetIsDied())
				OwnCharacter->SetIsDied(true);
	}
	SetHp(CurHp);
}

void UStatComponent::HealHp(float const& HealedHp)
{
	if (Hp == MaxHp)
		return;

	float CurHp = Hp;
	CurHp += HealedHp;

	if (CurHp >= MaxHp)
		CurHp = MaxHp;

	SetMp(CurHp);
}

void UStatComponent::SetHp(float const& _Hp)
{
	Hp = _Hp;

	OnHpChanged.Broadcast();
}

void UStatComponent::UseMana(float const& UsedMana)
{
	if (Mp == 0)
		return;

	float CurMp = Mp;
	CurMp -= UsedMana;

	if (CurMp <= 0)
		CurMp = 0;

	SetMp(CurMp);
}

void UStatComponent::HealMp(float const& HealedMp)
{
	if (Mp == MaxMp)
		return;

	float CurMp = Mp;
	CurMp += HealedMp;

	if (CurMp >= MaxMp)
		CurMp = MaxMp;

	SetMp(CurMp);
}

void UStatComponent::SetMp(float const& _Mp)
{
	Mp = _Mp;

	OnMpChanged.Broadcast();
}
