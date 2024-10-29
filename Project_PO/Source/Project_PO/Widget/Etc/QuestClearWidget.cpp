// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestClearWidget.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "../InGame/Slots/QuestItemWidget.h"
#include "../../Manager/BaseGameInstance.h"

UQuestClearWidget::UQuestClearWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, RewardID(-1)
{
	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("/Game/ThirdPerson/Blueprints/Widget/InGame/Slots/WBP_QuestItemSlot.WBP_QuestItemSlot_C"));
	if (UW.Succeeded())
		QuestItemWidget = UW.Class;
}

void UQuestClearWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateSlots();
}

void UQuestClearWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this] { RemoveFromParent(); }, 3.f, false);
}

void UQuestClearWidget::UpdateSlots()
{
	if (Wrap_QuestItems)
	{
		Wrap_QuestItems->ClearChildren();

		if (RewardID != -1) {
			UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
			if (GameInstance)
			{
				TWeakPtr<FQuestReward> RewardData = GameInstance->GetDatabaseMap<FQuestReward>(E_ManagerType::E_QuestRewardDatabaseManager, RewardID);
				if (RewardData.IsValid())
				{
					for (FRewardItem const& RewardItem : RewardData.Pin()->ItemRewards)
					{
						UQuestItemWidget* SlotsWidget = CreateWidget<UQuestItemWidget>(this, QuestItemWidget);
						if (SlotsWidget)
						{
							SlotsWidget->SetItemID(RewardItem.ItemID);
							SlotsWidget->SetAmount(RewardItem.Amount);
						}
						Wrap_QuestItems->AddChild(SlotsWidget);
					}
				}
			}
		}
		else
		{
			if (Txt_Reward)
				Txt_Reward->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	QuestClearAnim();
}

void UQuestClearWidget::QuestClearAnim()
{
	if (QuestAnim)
		PlayAnimation(QuestAnim);
}
