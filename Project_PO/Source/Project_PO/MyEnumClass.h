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
	E_CharWidget UMETA(DisplayName = "CharWidget"),
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
	E_Cunsumalbe UMETA(DisplayName = "Cunsum"),
	E_Etc UMETA(DisplayName = "Etc"),
	E_None UMETA(DisplayName = "None"),
};