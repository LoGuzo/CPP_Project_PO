// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../../../Manager/BaseGameInstance.h"
#include "../../../Manager/QuestManager.h"

UObjectiveSlotWidget::UObjectiveSlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ObjectiveID = -1;
}

void UObjectiveSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UQuestManager* QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
		if (QuestManager)
			QuestManager->OnObjectiveUpdated.AddUObject(this, &UObjectiveSlotWidget::BindWidget);
	}
}

void UObjectiveSlotWidget::SetUpWidget(int32 _ObjectiveID)
{
	if (_ObjectiveID != -1)
	{
		ObjectiveID = _ObjectiveID;
		UpdateWidget();
	}
}

void UObjectiveSlotWidget::UpdateWidget()
{
	if (ObjectiveID != -1)
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			TWeakPtr<FQuestObjective> ObjectiveData = GameInstance->GetDatabaseMap<FQuestObjective>(E_ManagerType::E_QuestObjectiveDatabaseManager, ObjectiveID);
			if (ObjectiveData.IsValid())
			{
				UTexture2D* ObjectiveImage = ObjectiveData.Pin()->ObjectiveImage.LoadSynchronous();
				if (Img_Objective)
				{
					Img_Objective->SetBrushFromTexture(ObjectiveImage);
					Img_Objective->SetVisibility(ESlateVisibility::Visible);
				}

				if (Txt_Description)
					Txt_Description->SetText(ObjectiveData.Pin()->ObjectiveDescription);

				if (Txt_Amount)
				{
					int32 CurAmount = ObjectiveData.Pin()->CurrentAmount;
					int32 RequiredAmount = ObjectiveData.Pin()->RequiredAmount;

					FString DisplayString = FString::Printf(TEXT("%d/%d"), CurAmount, RequiredAmount);
					Txt_Amount->SetText(FText::FromString(DisplayString));
				}
			}
		}
	}
}

void UObjectiveSlotWidget::BindWidget(int32 _ObjectiveID)
{
	if (_ObjectiveID != -1 && ObjectiveID == _ObjectiveID)
		UpdateWidget();
}
