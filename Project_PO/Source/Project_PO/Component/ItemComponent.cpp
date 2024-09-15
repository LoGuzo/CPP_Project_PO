// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemComponent.h"

// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UItemComponent::SetItem(int32 _ItemID)
{

}

