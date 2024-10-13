// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProtectActor.h"
#include "StatueProtectActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AStatueProtectActor : public ABaseProtectActor
{
	GENERATED_BODY()
	
public:
	AStatueProtectActor();

protected:
	virtual void BeginPlay() override;

public:
	void SetUpStatComponent();
};
