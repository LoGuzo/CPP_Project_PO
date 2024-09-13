// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleDoorActor.h"

ASingleDoorActor::ASingleDoorActor()
	: DirectionType(E_DirectionType::E_None)
{
	DoorType = E_DoorType::E_Single;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	if(Mesh)
		Mesh->SetupAttachment(RootComponent);
}

void ASingleDoorActor::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = Mesh->GetRelativeRotation();
	if (DirectionType == E_DirectionType::E_Right)
	{
		// Plus
		TargetRotation = InitialRotation + FRotator(0.f, 90.f, 0.f);
	}
	else if (DirectionType == E_DirectionType::E_Left)
	{
		// Minus
		TargetRotation = InitialRotation + FRotator(0.f, -90.f, 0.f);
	}
}

void ASingleDoorActor::OpenDoor(float Value)
{
	FRotator CurrentRotation = FMath::Lerp(InitialRotation, TargetRotation, Value);
	Mesh->SetRelativeRotation(CurrentRotation);
}
