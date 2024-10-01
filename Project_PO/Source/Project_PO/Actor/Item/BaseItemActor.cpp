// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemActor.h"
#include "../../Component/ItemComponent/ItemComponent.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/ObjectPoolManager.h"

ABaseItemActor::ABaseItemActor()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	RootComponent = StaticMesh;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void ABaseItemActor::BeginPlay()
{
	Super::BeginPlay();
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

void ABaseItemActor::SetState(bool NowState)
{
	SetActorHiddenInGame(!NowState);
	SetActorEnableCollision(NowState);
	SetActorTickEnabled(NowState);
}

void ABaseItemActor::SetItem(int32 _ID)
{
	if (ItemComponent)
	{
		ItemComponent->SetItem(_ID);
		SetMeshComponent(ItemComponent->GetMesh());
	}
}

void ABaseItemActor::ResetItem()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UObjectPoolManager* ObjectPoolManager = GameInstance->GetManager<UObjectPoolManager>(E_ManagerType::E_ObjectPoolManager);

		if (!ObjectPoolManager)
			return;
		ObjectPoolManager->ReleaseItem(this);

		StaticMesh = nullptr;
		SkeletalMesh = nullptr;
	}
}

