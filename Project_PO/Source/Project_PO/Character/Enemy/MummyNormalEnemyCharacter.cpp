// Fill out your copyright notice in the Description page of Project Settings.


#include "MummyNormalEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "../../AnimInstance/BaseEnemyAnimInstance.h"

AMummyNormalEnemyCharacter::AMummyNormalEnemyCharacter()
{
	SetCharacterMesh();
}

void AMummyNormalEnemyCharacter::SetCharacterMesh()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 70.f);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -73.f), FRotator(0.f, -68.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("/Game/Characters/Mummy/Animation/ABP_Mummy.ABP_Mummy_C"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
		AnimInstance = Cast<UBaseEnemyAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
			AnimInstance->SetOwnCharacter(this);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainAsset(TEXT("/Game/Characters/Mummy/Meshs/Mummy_Base.Mummy_Base"));
	if (MainAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MainAsset.Object);

	SetUpHeadCollision();
}

void AMummyNormalEnemyCharacter::SetUpHeadCollision()
{
	HeadCollision->SetCapsuleHalfHeight(30.0);
	HeadCollision->SetRelativeLocation(FVector(15.f, 0.f, 0.f));
	HeadCollision->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
}
