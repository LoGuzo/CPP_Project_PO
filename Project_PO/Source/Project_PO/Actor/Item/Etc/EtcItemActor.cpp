// Fill out your copyright notice in the Description page of Project Settings.


#include "EtcItemActor.h"
#include "../../../Component/ItemComponent/ItemComponent.h"

AEtcItemActor::AEtcItemActor()
{
	ItemType = E_ItemType::E_Etc;

	ItemComponent = CreateDefaultSubobject<UItemComponent>("ItemComponent");
	RootComponent = GetStaticMesh();
}
