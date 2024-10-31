// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEtcWidget.h"
#include "CharacterSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UCharacterSlotWidget : public UBaseEtcWidget
{
	GENERATED_BODY()
	
public:
	UCharacterSlotWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Char;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Class;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Class;

	UPROPERTY(meta = (BindWidget))
	class UProgressSegmentWidget* PB_Attack;

	UPROPERTY(meta = (BindWidget))
	class UProgressSegmentWidget* PB_Armor;

	UPROPERTY(meta = (BindWidget))
	class UProgressSegmentWidget* PB_Speed;

	UPROPERTY(meta = (BindWidget))
	class UProgressSegmentWidget* PB_AtkSpeed;

	UPROPERTY(meta = (BindWidget))
	class UProgressSegmentWidget* PB_Hp;

private:
	int32 ClassID;
	E_ClassType ClassType;

private:
	void SetUpProgressAttack(float const& Value);
	void SetUpProgressArmor(float const& Value);
	void SetUpProgressSpeed(float const& Value);
	void SetUpProgressAtkSpeed(float const& Value);
	void SetUpProgressHp(float const& Value);

public:
	void SetClassID(int32 const& _ClassID) { ClassID = _ClassID; }

	UFUNCTION()
	void ClickedCharBtn();

	class UButton* GetBtn() { return Btn_Char; }
};
