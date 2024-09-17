// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActorComponent.h"
#include "../MyEnumClass.h"
#include "../MyStructureAll.h"
#include "EquipComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PO_API UEquipComponent : public UBaseActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<E_EquipType, FItemData> EquipMap;

public:
	void SpawnWeapon(const E_WeaponType WeaponType, const int32 DataID);

	UFUNCTION(BlueprintCallable)
	void SetEquipment(const E_EquipType EquipType, const int32 DataID);
};
