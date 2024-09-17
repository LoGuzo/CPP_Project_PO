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

void ABaseItemActor::SetMeshComponent(TSoftObjectPtr<UStreamableRenderAsset> Mesh)
{
	UStaticMesh* staticMesh = Cast<UStaticMesh>(Mesh.LoadSynchronous());
	if (staticMesh)
	{
		GetStaticMesh()->SetStaticMesh(staticMesh);
	}
	else
	{
		USkeletalMesh* skeletalMesh = Cast<USkeletalMesh>(Mesh.LoadSynchronous());
		if (skeletalMesh)
		{
			GetSkeletalMesh()->SetSkeletalMesh(skeletalMesh);
		}
	}
}

void ABaseItemActor::SetItem(int32 _ID)
{
	ItemComponent->SetItem(_ID);
	SetMeshComponent(ItemComponent->GetMesh());
}

void ABaseItemActor::AfterDropItem()
{
	ItemComponent = nullptr;
	StaticMesh = nullptr;
	SkeletalMesh = nullptr;
}

