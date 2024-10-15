// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/WidgetManager.h"
#include "../../Widget/InGame/CharInfo/BossHpMainWidget.h"

#include "../../Component/StatComponent/MonsterStatComponent.h"

ABossEnemyCharacter::ABossEnemyCharacter()
{
}

void ABossEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABossEnemyCharacter::SetUpBossHp, 2.f, false);*/
}

void ABossEnemyCharacter::SetUpBossHp()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UBossHpMainWidget* BossHp = WidgetManager->GetWidget<UBossHpMainWidget>(TEXT("BossHp"));
			if (BossHp)
			{
				BossHp->SetBossHp(StatComponent);
			}
		}
	}
	if (StatComponent)
		GetStatComponent<UMonsterStatComponent>()->SetStat(ID);
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

void ABossEnemyCharacter::SetState(bool NowState)
{
	Super::SetState(NowState);
}
