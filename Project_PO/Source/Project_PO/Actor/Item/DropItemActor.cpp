// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItemActor.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "../../Character/Player/PlayerCharacter.h"

ADropItemActor::ADropItemActor()
{
	SetBoxComponent();
}

void ADropItemActor::Interact(AActor* PlayerCharacter)
{
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(PlayerCharacter);
	if (playerCharacter)
	{

		AfterDropItem();
	}

}

void ADropItemActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADropItemActor::SetState(bool NowState)
{
	SetActorHiddenInGame(!NowState);
	SetActorEnableCollision(NowState);
}

void ADropItemActor::AfterDropItem()
{
	Super::AfterDropItem();

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
		GetStaticMesh()->SetRelativeLocation(FVector(0.f, 0.f, -40.f));

		UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(GetStaticMesh()->GetMaterial(0), this);
		MaterialInstance->SetScalarParameterValue(TEXT("IsDropped"), 1.0f);
		GetStaticMesh()->SetMaterial(0, MaterialInstance);

		return;
	}

	USkeletalMesh* skeletalMesh = Cast<USkeletalMesh>(Mesh.LoadSynchronous());
	if (skeletalMesh)
	{
		GetSkeletalMesh()->SetSkeletalMesh(skeletalMesh);
		GetSkeletalMesh()->SetRelativeLocation(FVector(0.f, 0.f, -40.f));

		UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(GetSkeletalMesh()->GetMaterial(0), this);
		MaterialInstance->SetScalarParameterValue(TEXT("IsDropped"), 1.0f);
		GetSkeletalMesh()->SetMaterial(0, MaterialInstance);

		return;
	}
}