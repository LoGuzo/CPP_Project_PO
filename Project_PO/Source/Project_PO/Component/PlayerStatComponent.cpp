// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Manager/BaseGameInstance.h"

UPlayerStatComponent::UPlayerStatComponent()
{
	MaxLevel = 10;
}

void UPlayerStatComponent::SetStat(int32 const& _ID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FClassStatData> StatData = GameInstance->GetDatabaseMap<FClassStatData>(E_ManagerType::E_ClassDatabaseManager, _ID);
		if (StatData.IsValid())
		{
			ID = StatData.Pin()->ID;
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

void UPlayerStatComponent::SetLevel(int32 const& _Level)
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

void UPlayerStatComponent::SetExp(float const& TakedExp)
{
	if (Level == MaxLevel)
		return;

	Exp += TakedExp;
	if (Exp >= MaxExp)
	{
		Level += 1;
		SetLevel(Level);
	}

	OnExpChanged.Broadcast();
}