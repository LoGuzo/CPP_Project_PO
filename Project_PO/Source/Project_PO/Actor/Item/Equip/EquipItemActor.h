// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseItemActor.h"
#include "../../../MyEnumClass.h"
#include "EquipItemActor.generated.h"


UCLASS()
class PROJECT_PO_API AEquipItemActor : public ABaseItemActor
{
	GENERATED_BODY()
	
public:
	AEquipItemActor();

public:
	virtual void SetItem(int32 _ID) override;
};
