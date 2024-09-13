// Fill out your copyright notice in the Description page of Project Settings.


#include "BoyCharacter.h"
#include "Camera/CameraComponent.h"

ABoyCharacter::ABoyCharacter()
{
	SetCharacterMesh();

	// Set FollowCamera
	GetFollowCamera()->SetRelativeLocation(FVector(140.f, 70.f, 70.f));
}

void ABoyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABoyCharacter::SetCharacterMesh()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -96.f), FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("/Game/Characters/Boy/Animations/ABP_Boy.ABP_Boy_C"));
	if (ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(ANIM.Class);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainAsset(TEXT("/Game/Characters/Boy/Meshes/boy_scene1.boy_scene1"));
	if (MainAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MainAsset.Object);
}
