// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterStatComponent.h"
#include "../../Character/Enemy/EnemyCharacter.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/DatabaseManager/ClassDatabaseManager.h"

UMonsterStatComponent::UMonsterStatComponent()
{
}

void UMonsterStatComponent::SetStat(int32 const& _ID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FMonsterStatData> StatData = GameInstance->GetDatabaseMap<FMonsterStatData>(E_ManagerType::E_MonsterDatabaseManager, _ID);
		if (StatData.IsValid())
		{
			ID = StatData.Pin()->ID;
			MonsterName = StatData.Pin()->MonsterName;
			Attack = StatData.Pin()->Attack;
			Armor = StatData.Pin()->Armor;
			MaxHp = StatData.Pin()->MaxHp;
			SetHp(MaxHp);
			MaxMp = StatData.Pin()->MaxMp;
			Mp = MaxMp;
			RewardEXP = StatData.Pin()->RewardEXP;
			AttackRange = StatData.Pin()->AttackRange;

			AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetOwner());
			if (EnemyCharacter)
				EnemyCharacter->AddSkillMap(StatData.Pin()->SkillIDs);
		}
	}
}