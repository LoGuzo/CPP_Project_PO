// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEtcWidget.h"
#include "QuestClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UQuestClearWidget : public UBaseEtcWidget
{
	GENERATED_BODY()
	
public:
	UQuestClearWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Reward;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* Wrap_QuestItems;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* QuestAnim;

	TSubclassOf<class UQuestItemWidget> QuestItemWidget;

	int32 RewardID;

public:
	void SetRewardID(int32 _RewardID) { RewardID = _RewardID; }

private:
	void UpdateSlots();
	void QuestClearAnim();
};
