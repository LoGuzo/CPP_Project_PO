// Fill out your copyright notice in the Description page of Project Settings.


#include "GolemBossEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "../../AnimInstance/BaseEnemyAnimInstance.h"
#include "../../Controller/AI/BaseBossAIController.h"

AGolemBossEnemyCharacter::AGolemBossEnemyCharacter()
{
	SetActorScale3D(FVector(3.f, 3.f, 3.f));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -96.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	MonsterType = E_MonsterType::E_Golem;
	ID = 102;

	bIsReady = true;

	SetUpCharacter();

	AIControllerClass = ABaseBossAIController::StaticClass();
}

void AGolemBossEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGolemBossEnemyCharacter::SetCharacterMesh()
{
	Super::SetCharacterMesh();

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
}

void AGolemBossEnemyCharacter::SetUpHeadCollision()
{
	Super::SetUpHeadCollision();

	HeadCollision->SetCapsuleHalfHeight(22.0);
	HeadCollision->SetRelativeLocation(FVector(10.f, 13.f, 0.f));
}

void AGolemBossEnemyCharacter::SetUpArmCollision()
{
	Super::SetUpArmCollision();

	RightArmCollision->SetCapsuleHalfHeight(80.0);
	RightArmCollision->SetRelativeLocation(FVector(-60.f, -30.f, 0.f));
	RightArmCollision->SetRelativeRotation(FRotator(90.f, 90.f, 60.f));

	LeftArmCollision->SetCapsuleHalfHeight(80.0);
	LeftArmCollision->SetRelativeLocation(FVector(60.f, 30.f, 0.f));
	LeftArmCollision->SetRelativeRotation(FRotator(90.f, 90.f, 60.f));
}

void AGolemBossEnemyCharacter::SetUpLegCollision()
{
	Super::SetUpLegCollision();

	RightLegCollision->SetRelativeLocation(FVector(30.f, 0.f, 0.f));
	RightLegCollision->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));


	LeftLegCollision->SetRelativeLocation(FVector(-30.f, 0.f, 0.f));
	LeftLegCollision->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
}

void AGolemBossEnemyCharacter::SetUpBodyCollision()
{
	Super::SetUpBodyCollision();

	BodyCollision->InitCapsuleSize(30.f,50.f);
	BodyCollision->SetRelativeLocation(FVector(32.f, 4.f, 0.f));
	BodyCollision->SetRelativeRotation(FRotator(90.f, 0.f, -11.f));
}

void AGolemBossEnemyCharacter::Died()
{
	Super::Died();

	PlaySkill(TEXT("Golem Death"));
}

void AGolemBossEnemyCharacter::Attack(AActor* _Target)
{
	if (bIsAttack)
		return;

	PlaySkill(TEXT("Golem Attack"), 1.f);
	bIsAttack = true;
}

void AGolemBossEnemyCharacter::SetState(bool NowState)
{
	if (NowState)
		SetActorScale3D(FVector(3.f, 3.f, 3.f));

	Super::SetState(NowState);
}
