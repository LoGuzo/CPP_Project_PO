// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "../../Component/MonsterStatComponent.h"

AEnemyCharacter::AEnemyCharacter()
	: AnimInstance(nullptr)
{
    StatComponent = CreateDefaultSubobject<UMonsterStatComponent>("StatComponent");
}
 
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (StatComponent)
        StatComponent->SetStat(ID);
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    if (bIsDied)
        return 0.f;

    if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
    {
        FHitResult HitResult;
        const FPointDamageEvent& PointDamageEvent = static_cast<const FPointDamageEvent&>(DamageEvent);
        HitResult = PointDamageEvent.HitInfo;

        if (HitResult.GetComponent())
        {
            FString ComponentName = HitResult.GetComponent()->GetName();
            
            if (ComponentName == "HeadCollision")
            {
                DamageAmount *= 1.8f;
            }
            else if (ComponentName == "BodyCollision")
            {
                DamageAmount *= 1.0f;
            }
            else if (ComponentName == "RightArmCollision" || ComponentName == "LeftArmCollision")
            {
                DamageAmount *= 0.8f;
            }
            else if (ComponentName == "RightLegCollision" || ComponentName == "LeftLegCollision")
            {
                DamageAmount *= 0.5f;
            }
        }

        if (StatComponent)
            StatComponent->TakeDamage(DamageAmount);
    }

    return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
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
