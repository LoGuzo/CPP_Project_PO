// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoorActor.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseDoorActor::ABaseDoorActor()
	: DoorType(E_DoorType::E_None)
	, bIsOpened(false)
{
	PrimaryActorTick.bCanEverTick = true;

	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> CurveFloat(TEXT("/Game/TimeCurve/DoorCurve.DoorCurve"));

	if (CurveFloat.Succeeded())
		DoorCurve = CurveFloat.Object;
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

void ABaseDoorActor::Interact(APlayerCharacter* PlayerCharacter)
{
	if (!bIsOpened)
	{
		DoorTimeline->Play();
		bIsOpened = true;
	}
}

