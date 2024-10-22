// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Teleportable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTeleportable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_PO_API ITeleportable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Teleport() = 0;
};
