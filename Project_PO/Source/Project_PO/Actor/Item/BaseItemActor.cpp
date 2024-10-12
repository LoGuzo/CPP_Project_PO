// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemActor.h"
#include "../../Component/ItemComponent/ItemComponent.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/ObjectPoolManager.h"
#include "../../Manager/QuestManager.h"

ABaseItemActor::ABaseItemActor()
	: ItemType(E_ItemType::E_None)
	, EquipType(E_EquipType::E_None)
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

void ABaseItemActor::CheckingObjective()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UQuestManager* QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
		if (QuestManager)
			QuestManager->CheckingObjective(ItemComponent->GetID(), 1);
	}
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
		SetOwner(nullptr);
	}
}

