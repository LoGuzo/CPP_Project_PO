// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "GirlCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API AGirlCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	AGirlCharacter();

protected:
	virtual void BeginPlay() override;

private:
	void SetCharacterMesh();

protected:
	virtual void UsePotion() override;
	virtual void Died() override;
};
