// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"

AEnemyCharacter::AEnemyCharacter()
	: AnimInstance(nullptr)
{

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::SetUpCharacter()
{
	SetCharacterMesh();
	SetUpHeadCollision();
	SetUpBodyCollision();
	SetUpArmCollision();
	SetUpLegCollision();
}

void AEnemyCharacter::SetUpHeadCollision()
{
	HeadCollision = CreateDefaultSubobject<UCapsuleComponent>("HeadCollision");
	HeadCollision->SetupAttachment(GetMesh(), TEXT("head"));
	HeadCollision->SetCollisionProfileName(TEXT("Enemy"));
	HeadCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Owner;
}

void AEnemyCharacter::SetUpBodyCollision()
{
	BodyCollision = CreateDefaultSubobject<UCapsuleComponent>("BodyCollision");
	BodyCollision->SetupAttachment(GetMesh(), TEXT("pelvis"));
	BodyCollision->SetCollisionProfileName(TEXT("Enemy"));
	BodyCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Owner;
}
