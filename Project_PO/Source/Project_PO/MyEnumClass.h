// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_WeaponType : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_Pistol UMETA(DisplayName = "Pistol"),
	E_Rifle UMETA(DisplayName = "Rifle"),
	E_Shotgun UMETA(DisplayName = "Shotgun"),
};

UENUM(BlueprintType)
enum class E_WidgetType : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_HUD UMETA(DisplayName = "HUD"),
	E_MainMenu UMETA(DisplayName = "MainMenu"),
	E_InGame UMETA(DisplayName = "InGame"),
	E_PopUp UMETA(DisplayName = "PopUp"),
	E_Interaction UMETA(DisplayName = "Interaction"),
	E_Loading UMETA(DisplayName = "Loading"),
	E_Etc UMETA(DisplayName = "Etc"),
	E_CharWidget UMETA(DisplayName = "CharWidget"),
};
