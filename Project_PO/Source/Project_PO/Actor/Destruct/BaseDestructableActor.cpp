// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDestructableActor.h"
#include "Components/BoxComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

// Sets default values
ABaseDestructableActor::ABaseDestructableActor()
	: bIsDestroy(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetUpBoxComponent();
	SetUpGeometryComponent();
}

float ABaseDestructableActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDestroy)
		return 0.f;

	GeometryCollectionComponent->SetSimulatePhysics(true);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ABaseDestructableActor::DestroyObject, 2.f, false);

	bIsDestroy = true;

	return 0.f;
}

void ABaseDestructableActor::SetUpBoxComponent()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetCollisionProfileName("Enemy");
	BoxComponent->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	RootComponent = BoxComponent;
}

void ABaseDestructableActor::SetUpGeometryComponent()
{
	GeometryCollectionComponent = CreateDefaultSubobject<UGeometryCollectionComponent>("GeometryComponent");
	GeometryCollectionComponent->SetCollisionProfileName("CharacterMesh");
	GeometryCollectionComponent->SetSimulatePhysics(false);
	GeometryCollectionComponent->SetupAttachment(RootComponent);
}

void ABaseDestructableActor::DestroyObject()
{
	Destroy();
}
