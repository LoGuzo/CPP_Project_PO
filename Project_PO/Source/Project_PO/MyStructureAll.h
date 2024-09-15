// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnumClass.h"
#include "Engine/DataTable.h"
#include "MyStructureAll.generated.h"


USTRUCT(BlueprintType)
struct FQuestObjective : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    int32 ObjectiveID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    TEnumAsByte<E_ObjectiveType> ObjectiveType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    FText ObjectiveDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    int32 RequiredAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    int32 CurrentAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    bool bIsComplete;

    bool IsComplete() const
    {
        return CurrentAmount >= RequiredAmount;
    }
};

USTRUCT(BlueprintType)
struct FQuestReward : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
    int32 RewardID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
    float AcquiredEXP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
    TArray<int32> ItemRewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
    int32 AcquiredPoint;
};

USTRUCT(BlueprintType)
struct FQuestData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    int32 QuestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    int32 NextQuestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FText QuestName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FText QuestDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    TArray<int32> ObjectiveIDs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    int32 RewardID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    TEnumAsByte<E_QuestState> QuestState;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TSoftObjectPtr<UTexture2D> ItemImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 ItemStackSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TEnumAsByte <E_ItemType> ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    float DropChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TSoftObjectPtr<UStreamableRenderAsset> ItemMesh;
};
