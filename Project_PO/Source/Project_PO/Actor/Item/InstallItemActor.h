// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemActor.h"
#include "../../Interface/Installable.h"
#include "InstallItemActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AInstallItemActor : public ABaseItemActor, public IInstallable
{
	GENERATED_BODY()
	
public:
	AInstallItemActor();

public:
	virtual bool CanBePlaced(FVector const& Location) override;
	virtual void ShowPreview(FVector const& Location) override;
	virtual void Place(FVector const& Location, FRotator const& Rotation) override;
	
public:
	virtual void SetItem(int32 _ID) override;

	void ResetColor();

private:
	void UseItem();

private:
	UPROPERTY()
	UMaterialInterface* InstallMaterial;
	UPROPERTY()
	UMaterialInterface* BaseMaterial;
};
