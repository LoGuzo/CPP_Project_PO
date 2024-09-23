// Fill out your copyright notice in the Description page of Project Settings.


#include "EtcItemActor.h"
#include "../../../Component/ItemComponent/ItemComponent.h"

AEtcItemActor::AEtcItemActor()
{
	ItemComponent = CreateDefaultSubobject<UItemComponent>("ItemComponent");
	RootComponent = GetStaticMesh();
}
