// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../MyEnumClass.h"
#include "ObjectPoolManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UObjectPoolManager : public UObject
{
	GENERATED_BODY()
	
private:
	TArray<class AEnemyCharacter*> AvailableMonsters;

	// AActor -> ABaseItem
	TArray<AActor*> AvailableItems;

public:
	class AEnemyCharacter* GetMonster(E_MonsterType Type);
	void ReleaseMonster(AEnemyCharacter* Monster);

	// ItemPooling도 만들어야함
};
