// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/DatabaseManager/ClassDatabaseManager.h"

UStatComponent::UStatComponent()
{
	MaxLevel = 10;
}

void UStatComponent::SetStat(int32 const& _ClassID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FClassStatData> StatData = GameInstance->GetDatabaseMap<FClassStatData>(E_ManagerType::E_ClassDatabaseManager, _ClassID);
		if (StatData.IsValid())
		{
			ClassID = StatData.Pin()->ID;
			ClassType = StatData.Pin()->ClassType;
			Attack = StatData.Pin()->Attack;
			Armor = StatData.Pin()->Armor;
			Speed = StatData.Pin()->Speed;
			AttackSpeed = StatData.Pin()->AttackSpeed;
			MaxHp = StatData.Pin()->MaxHp;
			MaxMp = StatData.Pin()->MaxMp;
			MaxExp = StatData.Pin()->MaxExp;
		}
	}
	SetLevel(1);
}

void UStatComponent::SetLevel(int32 const& _Level)
{
	Level = _Level;
	Attack = Attack + ((Level - 1) * 3.f);
	Armor = Armor + ((Level - 1) * 2.f);
	MaxHp = MaxHp + ((Level - 1) * 10.f);
	Hp = MaxHp;
	MaxMp = MaxMp + ((Level - 1) * 5.f);
	Mp = MaxMp;
	MaxExp = MaxExp + ((Level - 1) * 30.f);
	Exp = MaxExp;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (PlayerCharacter)
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void UStatComponent::TakeDamage(float const& TakedDamage)
{
	if (Hp == 0)
		return;

	Hp -= TakedDamage;

	if (Hp <= 0)
	{
		Hp = 0;
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
		if (PlayerCharacter)
			if(!PlayerCharacter->GetIsDied())
				PlayerCharacter->SetIsDied(true);
		return;
	}
}

void UStatComponent::HealHp(float const& HealedHp)
{
	if (Hp == MaxHp)
		return;

	Hp += HealedHp;

	if (Hp >= MaxHp)
		Hp = MaxHp;
}

void UStatComponent::UseMana(float const& UsedMana)
{
	if (Mp == 0)
		return;

	Mp -= UsedMana;
	if (Mp <= 0)
		Mp = 0;
}

void UStatComponent::HealMp(float const& HealedMp)
{
	if (Mp == MaxMp)
		return;

	Mp += HealedMp;
	if (Mp >= MaxMp)
		Mp = MaxMp;
}

void UStatComponent::SetExp(float const& TakedExp)
{
	if (Level == MaxLevel)
		return;

	Exp += TakedExp;
	if (Exp >= MaxExp)
	{
		Level += 1;
		SetLevel(Level);
	}
}