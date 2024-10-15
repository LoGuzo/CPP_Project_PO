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

	int32 AttackIndex;

	UPROPERTY(VisibleAnywhere)
	class UStatComponent* StatComponent;

	UPROPERTY()
	TMap<FString, int32 > AnimMontageMap;

protected:
	TSoftObjectPtr<UAnimMontage> FindMontage(int32 const& MontageID);

public:
	bool GetIsAttack() { return bIsAttack; }
	void SetIsAttack(bool _bIsAttack) { bIsAttack = _bIsAttack; }

	bool GetIsDied() { return bIsDied; }
	void SetIsDied(bool _bIsDied) { bIsDied = _bIsDied; }

	virtual void SetState(bool NowState);

	int32 GetID() { return ID; }
	void SetID(int32 _ID) { ID = _ID; }

	virtual void AttackMontage() {};
	void AnimMontage(FString const& MontageName);

	template<typename T>
	T* GetStatComponent()
	{
		return Cast<T>(StatComponent);
	}
};
