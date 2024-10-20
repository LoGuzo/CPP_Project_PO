// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAnimInstance.h"
#include "../Character/Enemy/EnemyCharacter.h"

UBaseEnemyAnimInstance::UBaseEnemyAnimInstance()
	: bIsReady(false)
	, AttackIndex(0)
{
}

void UBaseEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnCharacter)
	{
		AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnCharacter);
		if (Enemy)
			bIsReady = Enemy->GetIsReady();
	}
}

void UBaseEnemyAnimInstance::JumpToSection()
{
	if (!NowData)
		return;

	UAnimMontage* AnimMontage = FindMontage(NowData->MontageID).LoadSynchronous();
	if (AnimMontage)
	{
		FName Name = GetAnimMontageName(AttackIndex);

		if (AnimMontage->IsValidSectionName(Name))
		{
			AttackIndex = (AttackIndex + 1) % 2;
			Montage_JumpToSection(Name, AnimMontage);
		}
	}
}

FName UBaseEnemyAnimInstance::GetAnimMontageName(int32 SectionIndex)
{
	return FName(FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UBaseEnemyAnimInstance::PlaySome(FBaseSkillData* Data, float AttackSpeed)
{
	Super::PlaySome(Data, AttackSpeed);

	JumpToSection();
}

void UBaseEnemyAnimInstance::AnimNotify_Ready()
{
	if (OwnCharacter)
	{
		AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnCharacter);
		if (Enemy)
			Enemy->SetIsReady(true);
	}
}
