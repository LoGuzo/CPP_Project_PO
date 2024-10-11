// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "../../Character/Player/PlayerCharacter.h"
#include "../../Component/InventoryComponent.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/WidgetManager.h"
#include "../../Manager/QuestManager.h"
#include "../../Widget/PopUp/AccessAlertWidget.h"

// Sets default values
AInteractActor::AInteractActor()
	: RequiredQuestID(-1)
	, RequiredItemID(-1)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetBoxComponent();
}

void AInteractActor::SetBoxComponent()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	BoxCollision->SetCollisionProfileName(TEXT("InteractObject"));
	RootComponent = BoxCollision;
}

bool AInteractActor::CheckingRequiredQuest()
{
	if (RequiredQuestID != -1)
	{
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			UQuestManager* QuestManager = GameInstance->GetManager<UQuestManager>(E_ManagerType::E_QuestManager);
			if (QuestManager)
			{
				if (!QuestManager->IsCompleteQuest(RequiredQuestID))
				{
					SetUpAlertWidget(E_Access::E_QuestAccess);
					return false;
				}
			}
		}
	}
	return true;
}

void AInteractActor::SetUpAlertWidget(E_Access _Type)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UAccessAlertWidget* AccessAlertWidget = WidgetManager->GetWidget<UAccessAlertWidget>(TEXT("Alert"));
			if (AccessAlertWidget)
			{
				AccessAlertWidget->SetUpText(_Type);
				
				if(!AccessAlertWidget->IsInViewport())
					AccessAlertWidget->AddToViewport();
			}
		}
	}
}

bool AInteractActor::CheckingRequiredItem(AActor* PlayerCharacter)
{
	if (CheckingRequiredQuest())
	{
		if (RequiredItemID != -1)
		{
			APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(PlayerCharacter);
			if (playerCharacter)
			{
				UInventoryComponent* InventoryComponent = playerCharacter->GetInventoryComponent();
				if (InventoryComponent)
				{
					UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
					if (GameInstance)
					{
						TWeakPtr<FItemData> ItemData = GameInstance->GetDatabaseMap<FItemData>(E_ManagerType::E_ItemDatabaseManager, RequiredItemID);
						if (ItemData.IsValid())
						{
							FResult result = InventoryComponent->FindSlot(RequiredItemID, ItemData.Pin()->ItemType.ItemType);
							if (!result.IsFindItem)
							{
								SetUpAlertWidget(E_Access::E_ItemAccess);
								return false;
							}
							InventoryComponent->UseItem(result.Index, ItemData.Pin()->ItemType);
						}
					}
				}
			}
		}
	}
	return true;
}