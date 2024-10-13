// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProtectActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../../Character/Player/PlayerCharacter.h"
#include "../../Component/StatComponent/MonsterStatComponent.h"

// Sets default values
ABaseProtectActor::ABaseProtectActor()
	: bIsDied(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	CapsuleCollision->SetCollisionProfileName(TEXT("ProtectObject"));
	RootComponent = CapsuleCollision;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticComponent");
	StaticMeshComponent->SetupAttachment(RootComponent);

	Statcomponent = CreateDefaultSubobject<UMonsterStatComponent>("StatComponent");
}

// Called when the game starts or when spawned
void ABaseProtectActor::BeginPlay()
{
	Super::BeginPlay();
}

float ABaseProtectActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(DamageCauser);
	if (PlayerCharacter)
		return 0.f;

	if (bIsDied)
		return 0.f;

	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Statcomponent->GetHp() <= 0)
	{
		bIsDied = true;
		SetState(false);
	}
	else
	{
		Statcomponent->TakeDamage(Damage);
	}

	return Damage;
}

void ABaseProtectActor::SetState(bool NowState)
{
	SetActorHiddenInGame(!NowState);
	SetActorEnableCollision(NowState);
	SetActorTickEnabled(NowState);
}