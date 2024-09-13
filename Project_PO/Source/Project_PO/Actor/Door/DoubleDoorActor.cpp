// Fill out your copyright notice in the Description page of Project Settings.


#include "DoubleDoorActor.h"

ADoubleDoorActor::ADoubleDoorActor()
{
	DoorType = E_DoorType::E_Double;

	RightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	LeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	if (RightMesh && LeftMesh)
	{
		RightMesh->SetupAttachment(RootComponent);
		LeftMesh->SetupAttachment(RootComponent);
	}
}

void ADoubleDoorActor::BeginPlay()
{
	Super::BeginPlay();

	RightInitialRotation = RightMesh->GetRelativeRotation();
	RightTargetRotation = RightInitialRotation + FRotator(0.f, 90.f, 0.f);
		
	LeftInitialRotation = LeftMesh->GetRelativeRotation();
	LeftTargetRotation = LeftInitialRotation + FRotator(0.f, -90.f, 0.f);
}

void ADoubleDoorActor::OpenDoor(float Value)
{
	FRotator RightCurrentRotation = FMath::Lerp(RightInitialRotation, RightTargetRotation, Value);
	RightMesh->SetRelativeRotation(RightCurrentRotation);

	FRotator LeftCurrentRotation = FMath::Lerp(LeftInitialRotation, LeftTargetRotation, Value);
	LeftMesh->SetRelativeRotation(LeftCurrentRotation);
}

