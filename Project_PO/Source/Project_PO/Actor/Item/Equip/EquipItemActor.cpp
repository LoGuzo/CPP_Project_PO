// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipItemActor.h"
#include "../../../Component/ItemComponent/EquipItemComponent.h"

AEquipItemActor::AEquipItemActor()
	: EquipType(E_EquipType::E_None)
{
	ItemComponent = CreateDefaultSubobject<UEquipItemComponent>("ItemComponent");
	RootComponent = GetSkeletalMesh();
}

void AEquipItemActor::SetItem(int32 _ID)
{
	if (ItemComponent)
	{
		UEquipItemComponent* EquipItemComp = GetItemComponent<UEquipItemComponent>();
		EquipItemComp->SetItem(_ID);
		SetMeshComponent(EquipItemComp->GetMesh());
	}
}
