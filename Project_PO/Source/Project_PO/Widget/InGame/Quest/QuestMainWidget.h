// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseInGameWidget.h"
#include "QuestMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UQuestMainWidget : public UBaseInGameWidget
{
	GENERATED_BODY()
public:
	UQuestMainWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
	TSubclassOf<class UObjectiveSlotWidget> ObjectiveSlotWidget;

private:
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* Box_Quest;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Description;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* Box_None;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* Box_Objective;

private:
	int32 QuestID;

private:
	void SetUpObjectiveSlot(const TArray<int32> ObjectiveIDs);

public:
	void SetUpWidget(int32 _QuestID);
	void UpdateWidget();
};
