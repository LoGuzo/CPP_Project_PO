// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePopUpWidget.h"
#include "AccessAlertWidget.generated.h"

UENUM()
enum E_Access
{
	E_QuestAccess,
	E_ItemAccess,
};

UCLASS()
class PROJECT_PO_API UAccessAlertWidget : public UBasePopUpWidget
{
	GENERATED_BODY()
	
public:
	UAccessAlertWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Access;

public:
	void SetUpText(E_Access _Type);
};
