// Fill out your copyright notice in the Description page of Project Settings.


#include "CunsumItemActor.h"
#include "../../../Component/ItemComponent/CunsumItemComponent.h"

ACunsumItemActor::ACunsumItemActor()
{
	ItemType = E_ItemType::E_Cunsumable;
	ItemComponent = CreateDefaultSubobject<UCunsumItemComponent>("ItemComponent");
	RootComponent = GetStaticMesh();
}

void ACunsumItemActor::SetItem(int32 _ID)
{
	if (ItemComponent)
	{
		UCunsumItemComponent* CunsumItemComp = GetItemComponent<UCunsumItemComponent>();
		CunsumItemComp->SetItem(_ID);
		SetMeshComponent(CunsumItemComp->GetMesh());
	}
}
