// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Installable.generated.h"

UINTERFACE(MinimalAPI)
class UInstallable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_PO_API IInstallable
{
	GENERATED_BODY()

public:
    virtual bool CanBePlaced(FVector const& Location) = 0;

    virtual void ShowPreview(FVector const& Location) = 0;

    virtual void Place(FVector const& Location, FRotator const& Rotation) = 0;
};
