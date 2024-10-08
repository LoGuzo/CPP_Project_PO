// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_WeaponType : uint8
{
	E_Pistol UMETA(DisplayName = "Pistol"),
	E_Rifle UMETA(DisplayName = "Rifle"),
	E_Shotgun UMETA(DisplayName = "Shotgun"),
	E_None UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class E_WidgetType : uint8
{
	E_HUD UMETA(DisplayName = "HUD"),
	E_MainMenu UMETA(DisplayName = "MainMenu"),
	E_InGame UMETA(DisplayName = "InGame"),
	E_PopUp UMETA(DisplayName = "PopUp"),
	E_Interaction UMETA(DisplayName = "Interaction"),
	E_Loading UMETA(DisplayName = "Loading"),
	E_Etc UMETA(DisplayName = "Etc"),
	E_None UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class E_ManagerType : uint8
{
	E_WidgetManager UMETA(DisplayName = "WidgetManager"),
	E_ObjectPoolManager UMETA(DisplayName = "ObjectMonager"),
	E_QuestManager UMETA(DisplayName = "QuestManager"),
	E_ItemDatabaseManager UMETA(DisplayName = "ItemDatabaseManager"),
	E_MontageDatabaseManager UMETA(DisplayName = "MontageDatabaseManager"),
	E_ClassDatabaseManager UMETA(DisplayName = "ClassDatabaseManager"),
	E_MonsterDatabaseManager UMETA(DisplayName = "MonsterDatabaseManager"),
	E_QuestDatabaseManager UMETA(DisplayName = "QuestDatabaseManager"),
	E_QuestObjectiveDatabaseManager UMETA(DisplayName = "QuestObjectiveDatabaseManager"),
	E_QuestRewardDatabaseManager UMETA(DisplayName = "QuestRewardDatabaseManager"),
};

UENUM(BlueprintType)
enum class E_EquipType : uint8
{
	E_Weapon UMETA(DisplayName = "Weapon"),
	E_Hat UMETA(DisplayName = "Hat"),
	E_Shoes UMETA(DisplayName = "Shoes"),
	E_Chest UMETA(DisplayName = "Chest"),
	E_Gloves UMETA(DisplayName = "Gloves"),
	E_Registerable UMETA(DisplayName = "Register"),
	E_Installable UMETA(DisplayName = "Install"),
	E_None UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class E_ObjectiveType : uint8
{
	E_Collect UMETA(DisplayName = "Collect"),
	E_Kill UMETA(DisplayName = "Kill"),
	E_Interact UMETA(DisplayName = "Interact"),
	E_ReachLocation UMETA(DisplayName = "Reach Location"),
	E_None UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class E_QuestState : uint8
{
	E_NotStarted UMETA(DisplayName = "NotStarted"),
	E_InProgress UMETA(DisplayName = "InProgress"),
	E_Completed UMETA(DisplayName = "Completed"),
	E_None UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class E_ItemType : uint8
{
	E_Equip UMETA(DisplayName = "Equip"),
	E_Cunsumable UMETA(DisplayName = "Cunsum"),
	E_Etc UMETA(DisplayName = "Etc"),
	E_Drop UMETA(DisplayName = "Drop"),
	E_None UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class E_MonsterType : uint8
{
	E_Mummy UMETA(DisplayName = "Mummy"),
	E_Golem UMETA(DisplayName = "Golem"),
	E_None UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class E_ClassType : uint8
{
	E_Boy UMETA(DisplayName = "Boy"),
	E_Girl UMETA(DisplayName = "Girl"),
	E_Cat UMETA(DisplayName = "Cat"),
};

UENUM(BlueprintType)
enum class E_DamageType : uint8
{
	E_Normal UMETA(DisplayName = "Normal"),
	E_Critical UMETA(DisplayName = "Critical"),
};