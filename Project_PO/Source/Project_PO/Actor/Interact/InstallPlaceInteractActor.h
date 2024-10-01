// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractActor.h"
#include "../../Interface/Interactable.h"
#include "InstallPlaceInteractActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AInstallPlaceInteractActor : public AInteractActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	AInstallPlaceInteractActor();

public:
	virtual void Interact(class AActor* PlayerCharacter) override;

private:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	bool bIsInstall;

public:
	bool GetIsInstall() { return bIsInstall; }
};
