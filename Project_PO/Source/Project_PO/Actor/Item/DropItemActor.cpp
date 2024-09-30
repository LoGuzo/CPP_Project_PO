// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItemActor.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "../../Character/Player/PlayerCharacter.h"
#include "../../Component/InventoryComponent.h"
#include "../../Component/ItemComponent/ItemComponent.h"

ADropItemActor::ADropItemActor()
{
	ItemComponent = CreateDefaultSubobject<UItemComponent>("ItemComponent");
	SetBoxComponent();
}

void ADropItemActor::Interact(AActor* PlayerCharacter)
{
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(PlayerCharacter);
	if (playerCharacter)
	{
		if (!ItemComponent)
			return;

		UInventoryComponent* InventoryComponent = playerCharacter->GetInventoryComponent();
		if (InventoryComponent)
		{
			int32 ID = ItemComponent->GetID();
			FSpawnItemType Type = ItemComponent->GetItemType();

			InventoryComponent->AddItem(ID, 1, Type);
		}

		ResetItem();
	}
}

void ADropItemActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADropItemActor::ResetItem()
{
	Super::ResetItem();

	BoxCollision = nullptr;
}

void ADropItemActor::SetBoxComponent()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	BoxCollision->SetCollisionProfileName(TEXT("InteractObject"));
	RootComponent = BoxCollision;
}

void ADropItemActor::SetMeshComponent(TSoftObjectPtr<UStreamableRenderAsset> Mesh)
{
	UStaticMesh* staticMesh = Cast<UStaticMesh>(Mesh.LoadSynchronous());
	if (staticMesh)
	{
		GetStaticMesh()->SetStaticMesh(staticMesh);
		GetStaticMesh()->SetRelativeLocation(FVector(0.f, 0.f, -20.f));
		GetStaticMesh()->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

		int32 NumMaterials = GetStaticMesh()->GetNumMaterials();
		for (int32 i = 0; i < NumMaterials; i++)
		{
			UMaterialInterface* BaseMaterial = GetStaticMesh()->GetMaterial(i);
			if (BaseMaterial)
			{
				UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);
				if (MaterialInstance)
				{
					MaterialInstance->SetScalarParameterValue(TEXT("IsDropped"), 1.0f);
					GetStaticMesh()->SetMaterial(i, MaterialInstance);
				}
			}
		}

		return;
	}

	USkeletalMesh* skeletalMesh = Cast<USkeletalMesh>(Mesh.LoadSynchronous());
	if (skeletalMesh)
	{
		GetSkeletalMesh()->SetSkeletalMesh(skeletalMesh);
		GetSkeletalMesh()->SetRelativeLocation(FVector(0.f, 0.f, -20.f));
		GetSkeletalMesh()->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

		int32 NumMaterials = GetSkeletalMesh()->GetNumMaterials();
		for (int32 i = 0; i < NumMaterials; i++)
		{
			UMaterialInterface* BaseMaterial = GetSkeletalMesh()->GetMaterial(i);
			if (BaseMaterial)
			{
				UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);
				if (MaterialInstance)
				{
					MaterialInstance->SetScalarParameterValue(TEXT("IsDropped"), 1.0f);
					GetSkeletalMesh()->SetMaterial(i, MaterialInstance);
				}
			}
		}
		return;
	}
}