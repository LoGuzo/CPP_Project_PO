// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemActor.h"
#include "../../Component/ItemComponent.h"

ABaseItemActor::ABaseItemActor()
{
	ItemComponent = CreateDefaultSubobject<UItemComponent>("ItemComponent");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(RootComponent);
}

void ABaseItemActor::AfterDropItem()
{
	ItemComponent = nullptr;
	StaticMesh = nullptr;
	SkeletalMesh = nullptr;
}

