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
	TMap<E_EquipType, FEquipItemData> EquipMap;

	UPROPERTY()
	class ABaseWeaponActor* CurrentWeapon;

public:
	void SpawnWeapon(const E_WeaponType WeaponType, const int32 DataID);

	void SetEquipment(const E_EquipType EquipType, const FEquipItemData ItemData);

	class ABaseWeaponActor* GetCurrentWeapon() { return CurrentWeapon; }
};
