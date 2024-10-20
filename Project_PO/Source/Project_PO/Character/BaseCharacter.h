// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class PROJECT_PO_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	// To add mapping context
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (AllowPrivateAccess = "true"))
	bool bIsAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Die, meta = (AllowPrivateAccess = "true"))
	bool bIsDied;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ID, meta = (AllowPrivateAccess = "true"))
	int32 ID;

	UPROPERTY(VisibleAnywhere)
	class UStatComponent* StatComponent;

	UPROPERTY(VisibleAnywhere)
	class USkillComponent* SkillComponent;

	UPROPERTY()
	TMap<FString, int32 > SkillMontageMap;

public:
	template<typename T>
	T* GetStatComponent()
	{
		return Cast<T>(StatComponent);
	}

	template<typename T>
	T* GetSkillComponent()
	{
		return Cast<T>(SkillComponent);
	}

	bool GetIsAttack() { return bIsAttack; }
	void SetIsAttack(bool _bIsAttack) { bIsAttack = _bIsAttack; }

	bool GetIsDied() { return bIsDied; }
	void SetIsDied(bool _bIsDied) { bIsDied = _bIsDied; }

	virtual void SetState(bool NowState);

	int32 GetID() { return ID; }
	void SetID(int32 _ID) { ID = _ID; }

	virtual void ControlSkill(int32 const& SkillID);
	virtual void PlaySkill(FString const& SkillName, float const& AttackSpeed = 1.f);
	void AddSkillMap(TArray<int32> SkillIDs);

	virtual void MeleeAttackCheck(float const& Range, float const& Coefficient) {};
	virtual void ScopeAttackCheck(float const& Range, float const& Coefficient) {};
	virtual void ShotAttackCheck() {};

	virtual void Died();
	virtual void DiedNotify();
};
