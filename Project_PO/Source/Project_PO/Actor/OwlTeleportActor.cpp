// Fill out your copyright notice in the Description page of Project Settings.


#include "OwlTeleportActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/StaticMesh.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Widget/Interaction/OwlInteractionWidget.h"

// Sets default values
AOwlTeleportActor::AOwlTeleportActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetBoxComponent();
	SetActorMesh();
}

void AOwlTeleportActor::SetBoxComponent()
{
	GetBoxComponent()->SetBoxExtent(FVector(100.f, 100.f, 100.f));
}

void AOwlTeleportActor::SetActorMesh()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (Mesh)
	{
		Mesh->SetupAttachment(RootComponent);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> ActorMesh(TEXT("/Game/Sky_Dungeon/meshes/props/SM_statue_02.SM_statue_02"));
		if (ActorMesh.Succeeded())
			Mesh->SetStaticMesh(ActorMesh.Object);
	}
}


void AOwlTeleportActor::Interact(AActor* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->SetActorLocation(TeleportLocation);
	}
}

