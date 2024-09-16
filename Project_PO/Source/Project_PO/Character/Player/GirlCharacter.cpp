// Fill out your copyright notice in the Description page of Project Settings.


#include "GirlCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../AnimInstance/BasePlayerAnimInstance.h"

AGirlCharacter::AGirlCharacter()
{
	SetCharacterMesh();
	GetCapsuleComponent()->InitCapsuleSize(42.f, 66.0f);

	GetCameraBoom()->SocketOffset = FVector(0.f, 40.f, 40.f);
	GetCameraBoom()->TargetArmLength = 200.0f;
}

void AGirlCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGirlCharacter::SetCharacterMesh()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -67.f), FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("/Game/Characters/Girl/Animations/ABP_Girl.ABP_Girl_C"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
		AnimInstance = Cast<UBasePlayerAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
			AnimInstance->SetOwnCharacter(this);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainAsset(TEXT("/Game/Characters/Girl/Meshes/arm_Tari_MRArm_dmx_MESH_001_ValveBiped_Bip01_Root.arm_Tari_MRArm_dmx_MESH_001_ValveBiped_Bip01_Root"));
	if (MainAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MainAsset.Object);
}
