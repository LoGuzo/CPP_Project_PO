// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"

AEnemyCharacter::AEnemyCharacter()
	: AnimInstance(nullptr)
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	SetUpHeadCollision();
}

void AEnemyCharacter::SetUpHeadCollision()
{
	HeadCollision = CreateDefaultSubobject<UCapsuleComponent>("HeadCollision");
	HeadCollision->SetupAttachment(GetMesh(), TEXT("head"));
	HeadCollision->SetCollisionProfileName(TEXT("Enemy"));
	HeadCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Owner;
}
