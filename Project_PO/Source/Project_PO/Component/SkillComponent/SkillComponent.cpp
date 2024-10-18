// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent.h"
#include "../../Character/BaseCharacter.h"
#include "../../Component/StatComponent/StatComponent.h"
#include "../../Manager/BaseGameInstance.h"


void USkillComponent::SetUpSkillMap(TArray<int32> SkillIDs)
{
	for (int32 const& SkillID : SkillIDs)
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			TWeakPtr<FBaseSkillData> Data = GameInstance->GetDatabaseMap<FBaseSkillData>(E_ManagerType::E_SkillDatabaseManager, SkillID);
			if (Data.IsValid())
				SkillMap.Emplace(SkillID, *Data.Pin());
		}
	}
}

void USkillComponent::UseSkill(int32 const& SkillID)
{
	FBaseSkillData* SkillData = SkillMap.Find(SkillID);
	ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwner());
	if (!SkillData && !Character)
		return;

	if (!SkillData->bIsReady)
		return;

	if (StatComponent->GetMp() < SkillData->MpCost)
		return;

	SkillData->bIsReady = false;

	GetWorld()->GetTimerManager().SetTimer(SkillData->SkillTimer, [this, SkillID]()
		{
			SetSkillIsReady(SkillID);
		}, SkillData->CoolTime, false);

	Character->PlaySkill(SkillData->SkillName.ToString(), StatComponent->GetAttackSpeed());
}

void USkillComponent::SetSkillIsReady(int32 const& SkillID)
{
	FBaseSkillData* SkillData = SkillMap.Find(SkillID);

	if (!SkillData->bIsReady)
		SkillData->bIsReady = true;
}