// Fill out your copyright notice in the Description page of Project Settings.


#include "GolemBossEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "../../AnimInstance/BaseEnemyAnimInstance.h"

AGolemBossEnemyCharacter::AGolemBossEnemyCharacter()
{
	SetCharacterMesh();
}

void AGolemBossEnemyCharacter::SetCharacterMesh()
{
	SetActorRelativeScale3D(FVector(3.f, 3.f, 3.f));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -96.f), FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM(TEXT("/Game/Characters/Golem/Animations/ABP_Golem.ABP_Golem_C"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
		AnimInstance = Cast<UBaseEnemyAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
			AnimInstance->SetOwnCharacter(this);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainAsset(TEXT("/Game/Characters/Golem/Mesh/SK_Golem.SK_Golem"));
	if (MainAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MainAsset.Object);

	SetUpHeadCollision();
	SetUpArmCollision();
	SetUpLegCollision();
}

void AGolemBossEnemyCharacter::SetUpHeadCollision()
{
	HeadCollision->SetCapsuleHalfHeight(22.0);
	HeadCollision->SetRelativeLocation(FVector(10.f, 13.f, 0.f));
}

void AGolemBossEnemyCharacter::SetUpArmCollision()
{
	RightArmCollision->SetCapsuleHalfHeight(80.0);
	RightArmCollision->SetRelativeLocation(FVector(-60.f, -30.f, 0.f));
	RightArmCollision->SetRelativeRotation(FRotator(90.f, 90.f, 60.f));

	LeftArmCollision->SetCapsuleHalfHeight(80.0);
	LeftArmCollision->SetRelativeLocation(FVector(60.f, 30.f, 0.f));
	LeftArmCollision->SetRelativeRotation(FRotator(90.f, 90.f, 60.f));
}

void AGolemBossEnemyCharacter::SetUpLegCollision()
{
	RightLegCollision->SetRelativeLocation(FVector(30.f, 0.f, 0.f));
	RightLegCollision->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));


	LeftLegCollision->SetRelativeLocation(FVector(-30.f, 0.f, 0.f));
	LeftLegCollision->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
}
