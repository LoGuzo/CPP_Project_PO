// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolManager.h"
#include "FactoryManager.h"
#include "SingletonManager.h"
#include "../Actor/Item/BaseItemActor.h"
#include "../Character/Enemy/EnemyCharacter.h"
#include "../Component/ItemComponent/ItemComponent.h"
#include "../Widget/PopUp/DamagePopUpWidget.h"

AEnemyCharacter* UObjectPoolManager::GetMonster(UWorld* World, E_MonsterType const& Type, FTransform const& Transform, const FActorSpawnParameters& SpawnParameters)
{
	if (!World)
		return nullptr;

	for (int32 i = 0; i < AvailableMonsters.Num(); i++)
	{
		if (AvailableMonsters[i] && AvailableMonsters[i]->GetMonsterType() == Type)
		{
			AEnemyCharacter* Monster = AvailableMonsters[i];
			Monster->SetState(true);
			Monster->SetActorTransform(Transform);
			AvailableMonsters.Remove(Monster);
			InUseMonsters.Add(Monster);
			return Monster;
		}
	}
	AEnemyCharacter* NewMonster = SingletonManager::GetInstance<UFactoryManager>()->MonsterFactory(World, Type, Transform, SpawnParameters);
	InUseMonsters.Add(NewMonster);

	return NewMonster;
}

void UObjectPoolManager::ReleaseMonster(AEnemyCharacter* Monster)
{
	if (Monster)
	{
		Monster->SetState(false);
		AvailableMonsters.Add(Monster);
		InUseMonsters.Remove(Monster);
	}
}

ABaseItemActor* UObjectPoolManager::GetItem(UWorld* World, FSpawnItemType const& Type, FTransform const& Transform, const FActorSpawnParameters& SpawnParameters)
{
	if (!World)
		return nullptr;

	for (int32 i = 0; i < AvailableItems.Num(); i++)
	{
		if (AvailableItems[i])
		{
			ABaseItemActor* Item = AvailableItems[i];

			if (Item->GetItemType() != Type.ItemType)
				continue;

			if(Item->GetEquipType() != Type.EquipType)
				continue;

			if (Type.ItemType == E_ItemType::E_Equip)
			{
				UItemComponent* ItemComponent = Item->GetItemComponent<UItemComponent>();
				if (!ItemComponent)
					continue;

				if (Type.EquipType == E_EquipType::E_Weapon && ItemComponent->GetItemType().WeaponType != Type.WeaponType)
					continue;
			}

			Item->SetState(true);
			AvailableItems.Remove(Item);
			InUseItems.Add(Item);
			return Item;
		}
	}

	ABaseItemActor* NewItem = SingletonManager::GetInstance<UFactoryManager>()->ItemFactory(World, Type, Transform, SpawnParameters);
	InUseItems.Add(NewItem);
	return NewItem;
}

void UObjectPoolManager::ReleaseItem(ABaseItemActor* Item)
{
	if (Item)
	{
		Item->SetState(false);
		AvailableItems.Add(Item);
		InUseItems.Remove(Item);
	}
}

UDamagePopUpWidget* UObjectPoolManager::GetWidget(UWorld* World, E_DamageType const& Type, TSubclassOf<UDamagePopUpWidget> WidgetClass, FVector2D const& Location, int32 const& Damage)
{
	UDamagePopUpWidget* Widget = nullptr;

	for (int32 i = 0; i < AvailableDamageWidgets.Num(); i++)
	{
		if (AvailableDamageWidgets[i])
		{
			Widget = AvailableDamageWidgets[i];
			AvailableDamageWidgets.Remove(Widget);
			InUseDamageWidgets.Add(Widget);
		}
	}

	if (!Widget)
	{
		Widget = SingletonManager::GetInstance<UFactoryManager>()->WidgetFactory(World, WidgetClass);
		InUseDamageWidgets.Add(Widget);
	}

	Widget->AddToViewport();
	FVector2D RandomLocation= RandomVector2D(Location, 50.f);
	Widget->SetPositionInViewport(RandomLocation);

	switch (Type)
	{
	case E_DamageType::E_Normal:
		Widget->SetDamageText(Damage);
		break;
	case E_DamageType::E_Critical:
		Widget->SetCriticalText(Damage);
		break;
	default:
		break;
	}

	return Widget;
}

void UObjectPoolManager::ReleaseWidget(UDamagePopUpWidget* Widget)
{
	if (Widget)
	{
		Widget->RemoveFromParent();
		AvailableDamageWidgets.Add(Widget);
		InUseDamageWidgets.Remove(Widget);
	}
}
