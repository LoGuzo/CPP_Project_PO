// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "StartPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AStartPlayerController : public ABasePlayerController
{
	GENERATED_BODY()
	
public:
	AStartPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UStartHUDWidget> StartHUDWidget;

private:
	void SetUpWidget();
};
