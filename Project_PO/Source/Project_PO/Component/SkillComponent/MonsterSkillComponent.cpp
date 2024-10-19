// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSkillComponent.h"

bool UMonsterSkillComponent::ChkSkillRange(AActor* _Target, int32& SkillID)
{
	if (_Target)
	{
		for (TPair<int32, FBaseSkillData>& SkillPair : SkillMap)
		{
			int32 skillID = SkillPair.Key;
			FBaseSkillData SkillData = SkillPair.Value;

			if (GetOwner())
			{
				float DistanceToTarget = FVector::Dist2D(GetOwner()->GetActorLocation(), _Target->GetActorLocation());
				float AttackRangeXScale = SkillData.AttackRange * (GetOwner()->GetActorScale3D().X);

				if (SkillData.bIsReady)
				{
					if (DistanceToTarget <= AttackRangeXScale)
					{
						SkillID = skillID;
						return true;
					}
				}
			}
		}
	}

	SkillID = -1;
	return false;
}