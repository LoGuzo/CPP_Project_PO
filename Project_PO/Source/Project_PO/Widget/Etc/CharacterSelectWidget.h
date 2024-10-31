// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEtcWidget.h"
#include "CharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UCharacterSelectWidget : public UBaseEtcWidget
{
	GENERATED_BODY()
	
public:
	UCharacterSelectWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* Wrap_Chars;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Back;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Select;

	TSubclassOf<class UCharacterSlotWidget> CharSlotWidget;

private:
	TArray<int32> ClassIDs;

public:
	void UpdatesSlots();

	UFUNCTION()
	void ClickedBackBtn();

	UFUNCTION()
	void ClickedCharBtn();
};
