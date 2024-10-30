// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../../MyEnumClass.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class USettingsWidget> SettingsWidget;

private:
	void SetUpSettingsWidget();
};
