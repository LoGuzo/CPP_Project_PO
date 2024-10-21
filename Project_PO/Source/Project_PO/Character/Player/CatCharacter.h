// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "CatCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ACatCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	ACatCharacter();

protected:
	virtual void BeginPlay() override;

private:
	void SetCharacterMesh();

protected:
	virtual void UsePotion() override;
};
