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

private:
	void SetCharacterMesh();
};
