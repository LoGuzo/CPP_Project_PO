// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "../../Character/Player/PlayerCharacter.h"

// Sets default values
AInteractActor::AInteractActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetBoxComponent();
}

// Called when the game starts or when spawned
void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AInteractActor::SetBoxComponent()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	BoxCollision->SetCollisionProfileName(TEXT("InteractObject"));
	RootComponent = BoxCollision;
}
