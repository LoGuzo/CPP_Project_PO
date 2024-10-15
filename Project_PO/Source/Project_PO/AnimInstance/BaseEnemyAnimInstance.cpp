// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAnimInstance.h"

UBaseEnemyAnimInstance::UBaseEnemyAnimInstance()
	: bIsWait(false)
{
}

void UBaseEnemyAnimInstance::JumpToSection(int32 SectionIndex, TSoftObjectPtr<UAnimMontage> Montage)
{
	UAnimMontage* AnimMontage = Montage.LoadSynchronous();
	if (AnimMontage)
	{
		FName Name = GetAnimMontageName(SectionIndex);
		Montage_JumpToSection(Name, AnimMontage);
	}
}

FName UBaseEnemyAnimInstance::GetAnimMontageName(int32 SectionIndex)
{
	return FName(FString::Printf(TEXT("Attack%d"), SectionIndex));
}