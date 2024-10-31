// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSlotWidget.h"
#include "ProgressSegmentWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../../Manager/BaseGameInstance.h"

UCharacterSlotWidget::UCharacterSlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ClassID(-1)
{
}

void UCharacterSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ClassID != -1) {
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			TWeakPtr<FClassStatData> ClassData = GameInstance->GetDatabaseMap<FClassStatData>(E_ManagerType::E_ClassDatabaseManager, ClassID);
			if (ClassData.IsValid())
			{
				if (Txt_Class)
					Txt_Class->SetText(ClassData.Pin()->ClassName);

				if (Img_Class)
					Img_Class->SetBrushFromSoftTexture(ClassData.Pin()->ClassImage);

				ClassType = ClassData.Pin()->ClassType;

				SetUpProgressAttack(ClassData.Pin()->Attack);
				SetUpProgressArmor(ClassData.Pin()->Armor);
				SetUpProgressSpeed(ClassData.Pin()->Speed);
				SetUpProgressAtkSpeed(ClassData.Pin()->AttackSpeed);
				SetUpProgressHp(ClassData.Pin()->MaxHp);
			}
		}
	}
}

void UCharacterSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Char)
		Btn_Char->OnClicked.AddDynamic(this, &UCharacterSlotWidget::ClickedCharBtn);
}

void UCharacterSlotWidget::SetUpProgressAttack(float const& Value)
{
	float AtkValue = Value / 100;

	if (PB_Attack)
		PB_Attack->SetSegment(AtkValue);
}

void UCharacterSlotWidget::SetUpProgressArmor(float const& Value)
{
	float Armor = Value / 50;

	if (PB_Armor)
		PB_Armor->SetSegment(Armor);
}

void UCharacterSlotWidget::SetUpProgressSpeed(float const& Value)
{
	float Speed = Value / 850;

	if (PB_Speed)
		PB_Speed->SetSegment(Speed);
}

void UCharacterSlotWidget::SetUpProgressAtkSpeed(float const& Value)
{
	float AtkSpeed = Value / 1.5;

	if (PB_AtkSpeed)
		PB_AtkSpeed->SetSegment(AtkSpeed);
}

void UCharacterSlotWidget::SetUpProgressHp(float const& Value)
{
	float Hp = Value / 1000;

	if (PB_Hp)
		PB_Hp->SetSegment(Hp);
}

void UCharacterSlotWidget::ClickedCharBtn()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
		GameInstance->SetClassType(ClassType);
}