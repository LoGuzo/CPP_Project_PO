// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "../../AnimInstance/BaseEnemyAnimInstance.h"
#include "../../Component/StatComponent/MonsterStatComponent.h"
#include "../../Controller/Player/BasePlayerController.h"
#include "../../Manager/BaseGameInstance.h"

AEnemyCharacter::AEnemyCharacter()
	: AnimInstance(nullptr)
{
	StatComponent = CreateDefaultSubobject<UMonsterStatComponent>("StatComponent");
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyMain"));
	Tags.Add(TEXT("Enemy"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (StatComponent)
		GetStatComponent<UMonsterStatComponent>()->SetStat(ID);
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDied)
		return 0.f;

	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FHitResult HitResult;
		const FPointDamageEvent& PointDamageEvent = static_cast<const FPointDamageEvent&>(DamageEvent);
		HitResult = PointDamageEvent.HitInfo;

		if (HitResult.GetComponent())
		{
			FString ComponentName = HitResult.GetComponent()->GetName();

			E_DamageType Type;
			FVector Location = GetActorLocation();

			if (ComponentName == "HeadCollision")
			{
				Damage *= 1.8f;
				Type = E_DamageType::E_Critical;
			}
			else if (ComponentName == "BodyCollision")
			{
				Damage *= 1.0f;
				Type = E_DamageType::E_Normal;
			}
			else if (ComponentName == "RightArmCollision" || ComponentName == "LeftArmCollision")
			{
				Damage *= 0.8f;
				Type = E_DamageType::E_Normal;
			}
			else if (ComponentName == "RightLegCollision" || ComponentName == "LeftLegCollision")
			{
				Damage *= 0.5f;
				Type = E_DamageType::E_Normal;
			}
			SetUpDamageWidget(EventInstigator, Type, Location, Damage);
		}

		if (StatComponent)
			StatComponent->TakeDamage(Damage);
	}

	return Damage;
}

void AEnemyCharacter::SetUpDamageWidget(AController* PlayerController, E_DamageType const& Type, FVector const& Location, int32 const& Damage)
{
	if (PlayerController)
	{
		ABasePlayerController* playerController = Cast<ABasePlayerController>(PlayerController);
		if (playerController)
			playerController->SetUpDamageWidget(Type, Location, Damage);
	}
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

void AEnemyCharacter::MeleeAttackCheck(float const& Range, float const& Coefficient)
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	float AttackRange = Range * GetActorScale3D().X;
	float AttackRadius = 50.f * GetActorScale3D().X;
	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResults,
		this->GetActorLocation(),
		this->GetActorLocation() + (this->GetActorForwardVector()) * (AttackRange),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

	FVector Vec = this->GetActorForwardVector() * AttackRange;
	FVector Center = this->GetActorLocation() + Vec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor = FColor::Red;

	for (FHitResult hitResult : HitResults)
	{
		if (bResult && hitResult.GetActor())
		{
			if (hitResult.GetActor()->ActorHasTag(TEXT("Player")))
			{
				UGameplayStatics::ApplyPointDamage(
					hitResult.GetActor(),
					StatComponent->GetAttack() * Coefficient,
					GetActorForwardVector(), hitResult,
					GetController(),
					this, UDamageType::StaticClass()
				);
			}
		}
	}
	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);
}