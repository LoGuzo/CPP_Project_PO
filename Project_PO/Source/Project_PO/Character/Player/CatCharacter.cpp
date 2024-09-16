// Fill out your copyright notice in the Description page of Project Settings.


#include "CatCharacter.h"
#include "Camera/CameraComponent.h"
#include "../../AnimInstance/BasePlayerAnimInstance.h"

ACatCharacter::ACatCharacter()
{
	SetCharacterMesh();
}

void ACatCharacter::SetCharacterMesh()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -96.f), FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("/Game/Characters/Cat/Animations/ABP_Cat.ABP_Cat_C"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
		AnimInstance = Cast<UBasePlayerAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
			AnimInstance->SetOwnCharacter(this);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainAsset(TEXT("/Game/Characters/Cat/Meshes/cat_08080404571.cat_08080404571"));
	if (MainAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MainAsset.Object);
}
