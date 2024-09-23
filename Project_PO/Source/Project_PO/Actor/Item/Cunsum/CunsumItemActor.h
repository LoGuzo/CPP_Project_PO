// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseItemActor.h"
#include "CunsumItemActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ACunsumItemActor : public ABaseItemActor
{
	GENERATED_BODY()
	
public:
	ACunsumItemActor();

public:
	virtual void SetItem(int32 _ID) override;
};
