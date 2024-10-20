// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalEnemyCharacter.h"
#include "Components/WidgetComponent.h"
#include "../../Widget/InGame/CharInfo/BaseHpInfoWidget.h"

ANormalEnemyCharacter::ANormalEnemyCharacter()
{
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	HpBar->SetupAttachment(RootComponent);

	static ConstructorHelpers::FClassFinder<UUserWidget>HpWidget(TEXT("/Game/ThirdPerson/Blueprints/Widget/InGame/CharInfo/WBP_HpBar.WBP_HpBar_C"));
	if (HpWidget.Succeeded())
	{
		HpBar->SetWidgetClass(HpWidget.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 300.f));
		HpBar->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	}
}

void ANormalEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HpBar->InitWidget();

	OnlyHpBar = Cast<UBaseHpInfoWidget>(HpBar->GetUserWidgetObject());
	if (OnlyHpBar)
	{
		OnlyHpBar->BindHp(StatComponent);
		OnlyHpBar->SetRenderOpacity(0.f);
	}
}

float ANormalEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDied)
		return 0.f;

	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	VisibleHpBar();

	return Damage;
}

void ANormalEnemyCharacter::VisibleHpBar()
{
	if (!bIsDied)
	{
		if (OnlyHpBar)
			OnlyHpBar->SetRenderOpacity(1.f);
	}
	else
	{
		if (OnlyHpBar)
			OnlyHpBar->SetRenderOpacity(0.f);
	}
}

void ANormalEnemyCharacter::Died()
{
	Super::Died();

	VisibleHpBar();
}
