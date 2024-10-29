// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHUDWidget.h"
#include "../../MyEnumClass.h"
#include "MyHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UMyHUDWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

public:
	UMyHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

private:
	TSubclassOf<class UMainInventoryWidget> InventoryWidget;
	TSubclassOf<class UAccessAlertWidget> AccessAlertWidget;
	TSubclassOf<class UBossHpMainWidget> BossHpMainWidget;
	TSubclassOf<class UTimerWidget> TimerWidget;
	TSubclassOf<class UQuestClearWidget> QuestClearWidget;

private:
	UPROPERTY(meta = (BindWidget))
	class UCharInfoWidget* WBP_CharInfo;

	UPROPERTY(meta = (BindWidget))
	class UCunsumQuickSlotWidget* WBP_CunsumQuickSlot;

	UPROPERTY(meta = (BindWidget))
	class USkillQuickSlotWidget* WBP_SkillQuickSlot;

	UPROPERTY(meta = (BindWidget))
	class UWeaponSlotWidget* WBP_WeaponSlot;

	UPROPERTY(meta = (BindWidget))
	class UQuestMainWidget* WBP_QuestMain;

public:
	void SetUpWidget();
	void SetUpCharInfo(class UStatComponent* StatComponent);
	void SetUpCunsumQuickSlot(class UPotionQuickSlotComponent* PotionQuickSlotComponent);
	void SetUpWeaponSlot(int32 const& ID);
	void SetUpQuestMain(int32 const& ID);

	class UCunsumQuickSlotWidget* GetCunsumQuickSlot() { return WBP_CunsumQuickSlot; }
	class USkillQuickSlotWidget* GetSkillQuickSlot() { return WBP_SkillQuickSlot; }
	class UQuestMainWidget* GetQuestMain() { return WBP_QuestMain; }
};
