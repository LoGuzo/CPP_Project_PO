// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "../../AnimInstance/BaseEnemyAnimInstance.h"
#include "../../Component/StatComponent/MonsterStatComponent.h"
#include "../../Component/SkillComponent/MonsterSkillComponent.h"
#include "../../Controller/Player/BasePlayerController.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/ObjectPoolManager.h"
#include "../../Manager/QuestManager.h"

AEnemyCharacter::AEnemyCharacter()
	: bIsReady(false)
	, AnimInstance(nullptr)
{
	StatComponent = CreateDefaultSubobject<UMonsterStatComponent>("StatComponent");
	SkillComponent = CreateDefaultSubobject<UMonsterSkillComponent>("MonsterSkillComponent");
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyMain"));
	Tags.Add(TEXT("Enemy"));

	AutoPossessAI = EAutoPossessAI::Spawned;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (StatComponent)
		GetStatComponent<UMonsterStatComponent>()->SetStat(ID);

	if (Controller && !AIController)
		AIController = Cast<AAIController>(Controller);
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

void AEnemyCharacter::UnPossesAIController()
{
	if (AIController)
		AIController->UnPossess();
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
	float HalfHeight = AttackRange * 0.5f + AttackRadius;

	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResults,
		GetActorLocation(),
		GetActorLocation() + (GetActorForwardVector()) * (AttackRange),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeCapsule(AttackRadius, HalfHeight),
		Params
	);

	FVector Vec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + Vec * 0.5f;

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
				DrawColor = FColor::Green;
			}
		}
	}
	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);
}

void AEnemyCharacter::ScopeAttackCheck(float const& Range, float const& Coefficient)
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	float AttackRange = Range * GetActorScale3D().X;
	float AttackRadius = 0.5f * AttackRange;

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + (GetActorForwardVector() * AttackRange);
	FVector Center = (StartLocation + EndLocation) * 0.5f;

	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResults,
		Center,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

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
				DrawColor = FColor::Green;
			}
		}
	}
	DrawDebugSphere(GetWorld(), Center, AttackRadius, 16, DrawColor, false, 2.f);
}

void AEnemyCharacter::AttackSkill(AActor* _Target, int32 const& SkillID)
{
	if (bIsDied || !_Target || bIsAttack || !bIsReady)
		return;

	Target = _Target;

	ControlSkill(SkillID);
}

AActor* AEnemyCharacter::SearchTarget()
{
	if (bIsDied || !Target || !bIsReady)
		return nullptr;

	return Target;
}

bool AEnemyCharacter::CanAttack(AActor* _Target)
{
	if (bIsDied || !_Target || bIsAttack || !bIsReady)
		return false;

	UMonsterStatComponent* MonsterStatComponent = GetStatComponent<UMonsterStatComponent>();
	if (!MonsterStatComponent)
		return false;

	float DistanceToTarget = FVector::Dist2D(GetActorLocation(), _Target->GetActorLocation()) - GetComponentWidth(_Target);

	bool bCanAttack = false;

	float AttackRange = MonsterStatComponent->GetAttackRange() * GetActorScale3D().X;

	if (DistanceToTarget <= AttackRange)
		bCanAttack = true;

	return bCanAttack;
}

bool AEnemyCharacter::CanUseSkill(AActor* _Target, int32& SkillID)
{
	UMonsterSkillComponent* MonsterSkillComponent = GetSkillComponent<UMonsterSkillComponent>();

	if (bIsDied || !MonsterSkillComponent || bIsAttack || !bIsReady)
	{
		SkillID = -1;
		return false;
	}

	return MonsterSkillComponent->ChkSkillRange(_Target, SkillID);
}

float AEnemyCharacter::GetComponentWidth(AActor* _Target)
{
	if (_Target)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(GetComponentByClass(UPrimitiveComponent::StaticClass()));

		if (Component)
		{
			FVector ComponentExtent = Component->Bounds.BoxExtent;
			float ComponentWidth = ComponentExtent.Y * 0.5f;

			return ComponentWidth;
		}
	}

	return -1;
}

void AEnemyCharacter::Died()
{
	Super::Died();
	
	QuestCheck();

	UnPossesAIController();
}

void AEnemyCharacter::DiedNotify()
{
	Super::DiedNotify();

	bIsDied = true;

	UnPossesAIController();

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UObjectPoolManager* ObjectPoolManager = GameInstance->GetManager<UObjectPoolManager>(E_ManagerType::E_ObjectPoolManager);
		if (ObjectPoolManager)
			ObjectPoolManager->ReleaseMonster(this);
	}
}

void AEnemyCharacter::SetState(bool NowState)
{
	Super::SetState(NowState);

	if (NowState && AIController)
		AIController->Possess(this);
}


void AEnemyCharacter::QuestCheck()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UQuestManager* QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
		if (QuestManager)
			QuestManager->CheckingObjective(ID, 1);
	}
}