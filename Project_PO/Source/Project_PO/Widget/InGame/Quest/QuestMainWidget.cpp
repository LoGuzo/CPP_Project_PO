// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestMainWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "../../../Manager/BaseGameInstance.h"
#include "../../../Manager/QuestManager.h"
#include "../../../Widget/InGame/Quest/ObjectiveSlotWidget.h"

UQuestMainWidget::UQuestMainWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget>ObjectSlot(TEXT("/Game/ThirdPerson/Blueprints/Widget/InGame/Quest/WBP_ObjectiveSlot.WBP_ObjectiveSlot_C"));
	if (ObjectSlot.Succeeded())
		ObjectiveSlotWidget = ObjectSlot.Class;
}

void UQuestMainWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Box_Quest)
		Box_Quest->SetVisibility(ESlateVisibility::Hidden);

	if (Box_Objective)
		Box_Objective->SetVisibility(ESlateVisibility::Hidden);

	if (Box_None)
		Box_None->SetVisibility(ESlateVisibility::Visible);
}

void UQuestMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UQuestManager* QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
		if (QuestManager)
			QuestManager->OnQuestUpdated.AddUObject(this, &UQuestMainWidget::SetUpWidget);
	}
}

void UQuestMainWidget::SetUpWidget(int32 _QuestID)
{
	if (_QuestID != -1)
	{
		QuestID = _QuestID;
		UpdateWidget();
	}
	else
	{
		if (Box_Quest)
			Box_Quest->SetVisibility(ESlateVisibility::Hidden);

		if (Box_Objective)
			Box_Objective->SetVisibility(ESlateVisibility::Hidden);

		if (Box_None)
			Box_None->SetVisibility(ESlateVisibility::Visible);
	}
}

void UQuestMainWidget::UpdateWidget()
{
	if (QuestID != -1)
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			TWeakPtr<FQuestData> QuestData = GameInstance->GetDatabaseMap<FQuestData>(E_ManagerType::E_QuestDatabaseManager, QuestID);
			if (QuestData.IsValid())
			{
				if (Box_Quest)
					Box_Quest->SetVisibility(ESlateVisibility::Visible);

				if (Txt_Name)
					Txt_Name->SetText(QuestData.Pin()->QuestName);

				if (Txt_Description)
					Txt_Description->SetText(QuestData.Pin()->QuestDescription);

				if (Box_Objective)
					Box_Objective->SetVisibility(ESlateVisibility::Visible);

				if (Box_None)
					Box_None->SetVisibility(ESlateVisibility::Hidden);

				SetUpObjectiveSlot(QuestData.Pin()->ObjectiveIDs);
			}
		}
	}
}

void UQuestMainWidget::SetUpObjectiveSlot(const TArray<int32> ObjectiveIDs)
{
	if (Box_Objective)
	{
		Box_Objective->ClearChildren();
		for (const int32& ObjectiveID : ObjectiveIDs)
		{
			UObjectiveSlotWidget* ObjectiveSlot = CreateWidget<UObjectiveSlotWidget>(this, ObjectiveSlotWidget);
			if (ObjectiveSlot)
			{
				ObjectiveSlot->SetUpWidget(ObjectiveID);
				Box_Objective->AddChild(ObjectiveSlot);
			}
		}
	}
}