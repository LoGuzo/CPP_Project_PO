// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEnemyCharacter.h"
#include "Components/CapsuleComponent.h"

ABossEnemyCharacter::ABossEnemyCharacter()
{
}

void ABossEnemyCharacter::SetUpArmCollision()
{
	Super::SetUpArmCollision();

	RightArmCollision = CreateDefaultSubobject<UCapsuleComponent>("RightArmCollision");
	RightArmCollision->SetupAttachment(GetMesh(), TEXT("upperarm_r"));
	RightArmCollision->SetCollisionProfileName(TEXT("Enemy"));
	RightArmCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Owner;

	LeftArmCollision = CreateDefaultSubobject<UCapsuleComponent>("LeftArmCollision");
	LeftArmCollision->SetupAttachment(GetMesh(), TEXT("upperarm_l"));
	LeftArmCollision->SetCollisionProfileName(TEXT("Enemy"));
	LeftArmCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Owner;
}

void ABossEnemyCharacter::SetUpLegCollision()
{
	Super::SetUpLegCollision();

	RightLegCollision = CreateDefaultSubobject<UCapsuleComponent>("RightLegCollision");
	RightLegCollision->SetupAttachment(GetMesh(), TEXT("thigh_r"));
	RightLegCollision->SetCollisionProfileName(TEXT("Enemy"));
	RightLegCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Owner;

	LeftLegCollision = CreateDefaultSubobject<UCapsuleComponent>("LeftLegCollision");
	LeftLegCollision->SetupAttachment(GetMesh(), TEXT("thigh_l"));
	LeftLegCollision->SetCollisionProfileName(TEXT("Enemy"));
	LeftLegCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Owner;
}
