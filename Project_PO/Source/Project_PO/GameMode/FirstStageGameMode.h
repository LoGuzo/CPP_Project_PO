// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStageGameMode.h"
#include "FirstStageGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AFirstStageGameMode : public ABaseStageGameMode
{
	GENERATED_BODY()
	
public:
	AFirstStageGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
