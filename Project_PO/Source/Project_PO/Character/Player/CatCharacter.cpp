// Fill out your copyright notice in the Description page of Project Settings.


#include "CatCharacter.h"
#include "Camera/CameraComponent.h"

ACatCharacter::ACatCharacter()
{
	SetCharacterMesh();

	// Set FollowCamera
	GetFollowCamera()->SetRelativeLocation(FVector(140.f, 70.f, 70.f));
}

void ACatCharacter::SetCharacterMesh()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -96.f), FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("/Game/Characters/Cat/Animations/ABP_Cat.ABP_Cat_C"));
	if (ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(ANIM.Class);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainAsset(TEXT("/Game/Characters/Cat/Meshes/cat_08080404571.cat_08080404571"));
	if (MainAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MainAsset.Object);
}
