// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterStatComponent.h"
#include "../Character/Enemy/EnemyCharacter.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/DatabaseManager/ClassDatabaseManager.h"

UMonsterStatComponent::UMonsterStatComponent()
{
}

void UMonsterStatComponent::SetStat(int32 MonsterID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FMonsterStatData> StatData = GameInstance->GetDatabaseMap<FMonsterStatData>(E_ManagerType::E_MonsterDatabaseManager, MonsterID);
		if (StatData.IsValid())
		{
			MonsterName = StatData.Pin()->MonsterName;
			Attack = StatData.Pin()->Attack;
			Armor = StatData.Pin()->Armor;
			MaxHp = StatData.Pin()->MaxHp;
			Hp = MaxHp;
			MaxMp = StatData.Pin()->MaxMp;
			Mp = MaxMp;
			RewardEXP = StatData.Pin()->RewardEXP;
		}
	}
}

void UMonsterStatComponent::TakeDamage(float const& TakedDamage)
{
	if (Hp == 0)
		return;

	Hp -= TakedDamage;

	if (Hp <= 0)
	{
		Hp = 0;
		AEnemyCharacter* MonsterCharacter = Cast<AEnemyCharacter>(GetOwner());
		if (MonsterCharacter)
			if (!MonsterCharacter->GetIsDied())
				MonsterCharacter->SetIsDied(true);
	}
}

void UMonsterStatComponent::HealHp(float const& HealedHp)
{
	if (Hp == MaxHp)
		return;

	Hp += HealedHp;

	if (Hp >= MaxHp)
		Hp = MaxHp;
}

void UMonsterStatComponent::UseMana(float const& UsedMana)
{
	if (Mp == 0)
		return;

	Mp -= UsedMana;
	if (Mp <= 0)
		Mp = 0;
}

void UMonsterStatComponent::HealMp(float const& HealedMp)
{
	if (Mp == MaxMp)
		return;

	Mp += HealedMp;
	if (Mp >= MaxMp)
		Mp = MaxMp;
}