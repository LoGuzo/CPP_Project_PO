// Fill out your copyright notice in the Description page of Project Settings.


#include "MummyNormalEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../AnimInstance/BaseEnemyAnimInstance.h"
#include "../../Component/StatComponent/MonsterStatComponent.h"
#include "../../Controller/AI/BaseNormalAIController.h"

AMummyNormalEnemyCharacter::AMummyNormalEnemyCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 70.f);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -73.f), FRotator(0.f, -90.f, 0.f));

	MonsterType = E_MonsterType::E_Mummy;
	ID = 101;

	SetUpCharacter();
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	AIControllerClass = ABaseNormalAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMummyNormalEnemyCharacter::SetCharacterMesh()
{
	Super::SetCharacterMesh();

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
}

void AMummyNormalEnemyCharacter::SetUpHeadCollision()
{
	Super::SetUpHeadCollision();

	HeadCollision->SetCapsuleHalfHeight(30.0);
	HeadCollision->SetRelativeLocation(FVector(15.f, 0.f, 0.f));
	HeadCollision->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
}

void AMummyNormalEnemyCharacter::SetUpBodyCollision()
{
	Super::SetUpBodyCollision();

	BodyCollision->InitCapsuleSize(30.f, 50.f);
	BodyCollision->SetRelativeLocation(FVector(-5.f, -5.f, 0.f));
	BodyCollision->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
}

void AMummyNormalEnemyCharacter::Attack()
{
	if (bIsAttack)
		return;

	PlaySkill(TEXT("Mummy Attack"), 1.f);
}

AActor* AMummyNormalEnemyCharacter::SearchTarget()
{
	return Super::SearchTarget();
}

bool AMummyNormalEnemyCharacter::CanAttack(AActor const* _Target)
{
	bool bChkParent = Super::CanAttack(_Target);

	if (!bChkParent)
		return false;

	UMonsterStatComponent* MonsterStatComponent = GetStatComponent<UMonsterStatComponent>();
	if (!MonsterStatComponent)
		return false;

	float DistanceToTarget = _Target->GetDistanceTo(this);

	bool bCanAttack = false;

	float AttackRange = MonsterStatComponent->GetAttackRange();

	if (DistanceToTarget <= AttackRange)
		bCanAttack = true;

	return bCanAttack;
}
