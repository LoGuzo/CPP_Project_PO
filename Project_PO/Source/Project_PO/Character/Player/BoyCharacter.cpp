// Fill out your copyright notice in the Description page of Project Settings.


#include "BoyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../AnimInstance/BasePlayerAnimInstance.h"

ABoyCharacter::ABoyCharacter()
{
	ID = 1;

	SetCharacterMesh();

	GetCameraBoom()->SocketOffset = FVector(0.f, 50.f, 70.f);
	GetCameraBoom()->TargetArmLength = 250.0f;

	AttackMontageMap.Emplace(E_WeaponType::E_Pistol, TEXT("Boy Pistol Attack"));
	AttackMontageMap.Emplace(E_WeaponType::E_Rifle, TEXT("Boy Rifle Attack"));
	AttackMontageMap.Emplace(E_WeaponType::E_Shotgun, TEXT("Boy Shotgun Attack"));
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
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
		AnimInstance = Cast<UBasePlayerAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
			AnimInstance->SetOwnCharacter(this);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainAsset(TEXT("/Game/Characters/Boy/Meshes/boy_scene1.boy_scene1"));
	if (MainAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MainAsset.Object);
}

void ABoyCharacter::UsePotion()
{
	PlaySkill(TEXT("Boy Drink Potion"));
}

void ABoyCharacter::Died()
{
	Super::Died();

	PlaySkill(TEXT("Boy Death"));
}
