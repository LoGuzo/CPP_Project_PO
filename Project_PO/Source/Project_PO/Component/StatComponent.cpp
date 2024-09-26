// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "../Character/BaseCharacter.h"
#include "../Manager/DatabaseManager/ClassDatabaseManager.h"

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

	Hp -= TakedDamage;

	if (Hp <= 0)
	{
		Hp = 0;
		ABaseCharacter* OwnCharacter = Cast<ABaseCharacter>(GetOwner());
		if (OwnCharacter)
			if (!OwnCharacter->GetIsDied())
				OwnCharacter->SetIsDied(true);
	}

	OnHpChanged.Broadcast();
}

void UStatComponent::HealHp(float const& HealedHp)
{
	if (Hp == MaxHp)
		return;

	Hp += HealedHp;

	if (Hp >= MaxHp)
		Hp = MaxHp;

	OnHpChanged.Broadcast();
}

void UStatComponent::UseMana(float const& UsedMana)
{
	if (Mp == 0)
		return;

	Mp -= UsedMana;
	if (Mp <= 0)
		Mp = 0;

	OnMpChanged.Broadcast();
}

void UStatComponent::HealMp(float const& HealedMp)
{
	if (Mp == MaxMp)
		return;

	Mp += HealedMp;
	if (Mp >= MaxMp)
		Mp = MaxMp;

	OnMpChanged.Broadcast();
}