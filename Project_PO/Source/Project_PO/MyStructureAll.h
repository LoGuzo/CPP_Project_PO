// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnumClass.h"
#include "Engine/DataTable.h"
#include "MyStructureAll.generated.h"


USTRUCT(BlueprintType)
struct FClassStatData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    E_ClassType ClassType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float Attack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float Armor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float Speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float AttackSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float MaxHp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float MaxMp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float MaxExp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    TArray<int32> SkillIDs;
};

USTRUCT(BlueprintType)
struct FMonsterStatData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat")
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat")
    E_MonsterType MonsterType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat")
    FName MonsterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat")
    float Attack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat")
    float Armor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat")
    float MaxHp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat")
    float MaxMp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat")
    float RewardEXP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat")
    float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStat")
    TArray<int32> SkillIDs;
};

USTRUCT(BlueprintType)
struct FQuestObjective : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    int32 TargetID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    int32 QuestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    E_ObjectiveType ObjectiveType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    FText ObjectiveDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    int32 RequiredAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    int32 CurrentAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    TSoftObjectPtr<UTexture2D> ObjectiveImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    bool bIsComplete;

    bool IsComplete() const
    {
        return CurrentAmount >= RequiredAmount;
    }

    void UpdateProgress(int32 Amount)
    {
        CurrentAmount += Amount;
        bIsComplete = IsComplete();
    }
};

USTRUCT(BlueprintType)
struct FRewardItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
    int32 ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
    int32 Amount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
    bool bIsIndividualReward;
};

USTRUCT(BlueprintType)
struct FQuestReward : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
    float AcquiredEXP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
    TArray<FRewardItem> ItemRewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
    int32 AcquiredPoint;
};


USTRUCT(BlueprintType)
struct FQuestData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    int32 NextQuestID = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FText QuestName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FText QuestDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    TArray<int32> ObjectiveIDs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    int32 RewardID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    E_QuestState QuestState;
};

USTRUCT(BlueprintType)
struct FSpawnItemType : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
    E_ItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
    E_EquipType EquipType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
    E_WeaponType WeaponType;

    FSpawnItemType() {};

    FSpawnItemType(E_ItemType _ItemType
        , E_EquipType _EquipType = E_EquipType::E_None
        , E_WeaponType _WeaponType = E_WeaponType::E_None)
    {
        ItemType = _ItemType;
        EquipType = _EquipType;
        WeaponType = _WeaponType;
    }
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TSoftObjectPtr<UTexture2D> ItemImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 ItemStackSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FSpawnItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    float DropChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TSoftObjectPtr<UStreamableRenderAsset> ItemMesh;
};

USTRUCT(BlueprintType)
struct FEquipItemData : public FItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    float AttackPower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    float DefensePower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    TSubclassOf<UAnimInstance> AnimInstance;
};

USTRUCT(BlueprintType)
struct FCunsumItemData : public FItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
    float RestoreAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
    float Duration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
    float Cooltime;
};

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
    FName MontageName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
    TSoftObjectPtr<UAnimMontage> Montage;
};

USTRUCT()
struct FBaseSkillData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    E_SkillType SkillType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FText SkillName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float MpCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    bool bIsReady = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float CoolTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float Range;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float Scale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float Coefficient;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FTimerHandle SkillTimer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    int32 MontageID;
};

USTRUCT()
struct FSkillData : public FBaseSkillData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
    FText SkillDesc;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
    int32 ReqLvl;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
    int32 CurLvl;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
    int32 MaxLvl;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
    UTexture2D* SkillImg;
};


USTRUCT()
struct FSlot
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, Category = "Item")
    int32 ItemID = -1;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    int32 Amount = 0;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    FSpawnItemType Type;
};
