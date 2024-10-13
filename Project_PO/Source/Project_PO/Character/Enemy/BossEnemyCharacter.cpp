// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/WidgetManager.h"
#include "../../Widget/InGame/CharInfo/BossHpMainWidget.h"


ABossEnemyCharacter::ABossEnemyCharacter()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>BossHpWidget(TEXT("/Game/ThirdPerson/Blueprints/Widget/InGame/CharInfo/WBP_BossHpMain.WBP_BossHpMain_C"));
	if (BossHpWidget.Succeeded())
		BossHpMainWidget = BossHpWidget.Class;
}

void ABossEnemyCharacter::BeginPlay()
{
	SetUpBossHp();

	Super::BeginPlay();
}

void ABossEnemyCharacter::SetUpBossHp()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			if (BossHpMainWidget)
			{
				UBossHpMainWidget* BossHp =	WidgetManager->CreateAndAddWidget<UWorld, UBossHpMainWidget>(GetWorld(), TEXT("BossHp"), BossHpMainWidget);
				if (BossHp)
				{
					BossHp->SetBossHp(StatComponent);
					BossHp->SetAddRemove();
				}
			}
		}
	}
}

void ABossEnemyCharacter::VisibleWidget()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			if (BossHpMainWidget)
			{
				UBossHpMainWidget* BossHp = WidgetManager->GetWidget<UBossHpMainWidget>(TEXT("BossHp"));
				if (BossHp)
					BossHp->SetAddRemove();
			}
		}
	}
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

	VisibleWidget();
}
