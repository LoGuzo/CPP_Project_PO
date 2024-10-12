// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoorActor.h"
#include "Components/AudioComponent.h"
#include "Curves/CurveFloat.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseDoorActor::ABaseDoorActor()
	: bIsOpened(false)
	, DoorType(E_DoorType::E_None)
{
	PrimaryActorTick.bCanEverTick = true;

	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	ParticleComponent->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	ParticleComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	ParticleComponent->bAutoActivate = false;
	ParticleComponent->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<UCurveFloat> CurveFloat(TEXT("/Game/TimeCurve/DoorCurve.DoorCurve"));
	if (CurveFloat.Succeeded())
		DoorCurve = CurveFloat.Object;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = false;

	InteractID = 6000;
	RequiredItemID = 1005;
}

void ABaseDoorActor::BeginPlay()
{
	Super::BeginPlay();

	if (DoorCurve)
	{
		InterpFunction.BindUFunction(this, FName("OpenDoor"));
		if (DoorTimeline)
		{
			DoorTimeline->AddInterpFloat(DoorCurve, InterpFunction);
			DoorTimeline->SetLooping(false);
		}
	}
}

void ABaseDoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DoorTimeline)
		DoorTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
}

void ABaseDoorActor::Interact(AActor* PlayerCharacter)
{
	if (!bIsOpened)
	{
		if (CheckingRequiredItem(PlayerCharacter))
		{
			if (ParticleComponent)
				ParticleComponent->Activate(true);

			if (AudioComponent)
				AudioComponent->Play();

			if (DoorTimeline)
				DoorTimeline->Play();

			CheckingObjective();

			bIsOpened = true;
		}
	}
}

