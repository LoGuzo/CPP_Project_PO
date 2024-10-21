// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipComponent.h"
#include "../Actor/Item/Equip/Weapon/BaseWeaponActor.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/ObjectPoolManager.h"
#include "../Manager/WidgetManager.h"
#include "../Widget/Etc/CrosshairEtcWidget.h"
#include "../Widget/HUD/MyHUDWidget.h"

// Sets default values for this component's properties
UEquipComponent::UEquipComponent()
	: CurrentWeapon(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEquipComponent::SpawnWeapon()
{
	if (OwnPlayer)
	{
		FEquipItemData ItemData = *EquipMap.Find(E_EquipType::E_Weapon);

		E_WeaponType WeaponType = ItemData.ItemType.WeaponType;

		OwnPlayer->SetWeaponType(WeaponType);
		UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			UObjectPoolManager* ObjectPoolManager = GameInstance->GetManager<UObjectPoolManager>(E_ManagerType::E_ObjectPoolManager);

			if (!ObjectPoolManager)
				return;

			if (CurrentWeapon)
			{
				CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				CurrentWeapon->ResetItem();
				CurrentWeapon = nullptr;
			}

			FSpawnItemType Type = FSpawnItemType(E_ItemType::E_Equip, E_EquipType::E_Weapon, WeaponType);

			FName SocketName;

			switch (WeaponType)
			{
			case E_WeaponType::E_Pistol:
				SocketName = FName(TEXT("pistol_socket"));
				break;
			case E_WeaponType::E_Rifle:
				SocketName = FName(TEXT("rifle_socket"));
				break;
			case E_WeaponType::E_Shotgun:
				SocketName = FName(TEXT("shotgun_socket"));
				break;
			default:
				break;
			}

			CurrentWeapon = Cast<ABaseWeaponActor>(ObjectPoolManager->GetItem(GetWorld(), Type, FTransform()));
			if (CurrentWeapon)
			{
				CurrentWeapon->SetItem(ItemData.ID);
				CurrentWeapon->SetOwner(OwnPlayer);
				CurrentWeapon->AttachToComponent(OwnPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
				SetUpWidget(ItemData.ID);

				if (CurrentWeapon->GetCrosshairWdiget())
				{
					UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
					if (WidgetManager)
					{
						APlayerController* PlayerController = Cast<APlayerController>(OwnPlayer->GetController());
						if (PlayerController)
						{
							UBaseUserWidget* CrossWidget = WidgetManager->CreateAndAddWidget<APlayerController, UCrosshairEtcWidget>(
								PlayerController,
								TEXT("CrosshairWidget"),
								CurrentWeapon->GetCrosshairWdiget()
							);
							if (CrossWidget)
								CrossWidget->SetAddRemove();
						}
					}
				}
			}
		}
	}
}

void UEquipComponent::SetEquipment(int32 const& ID)
{
	if (ID == -1)
		return;

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FEquipItemData> ItemData = GameInstance->GetDatabaseMap<FEquipItemData>(E_ManagerType::E_ItemDatabaseManager, ID);
		if (ItemData.IsValid())
		{
			E_EquipType Type = ItemData.Pin()->ItemType.EquipType;
			EquipMap.Emplace(Type, *ItemData.Pin());

			switch (Type)
			{
			case E_EquipType::E_Weapon:
				SpawnWeapon();
				break;
			case E_EquipType::E_Hat:
			case E_EquipType::E_Shoes:
			case E_EquipType::E_Chest:
			case E_EquipType::E_Gloves:
				break;
			default:
				break;
			}
		}
	}
}

void UEquipComponent::SetUpWidget(int32 const& ID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UWidgetManager* WidgetManager = GameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UMyHUDWidget* MyHUD = WidgetManager->GetWidget<UMyHUDWidget>(TEXT("HUD"));
			if (MyHUD)
				MyHUD->SetUpWeaponSlot(ID);
		}
	}
}
