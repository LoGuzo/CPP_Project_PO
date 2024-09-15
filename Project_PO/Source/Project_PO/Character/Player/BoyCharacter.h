// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "BoyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ABoyCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	ABoyCharacter();

protected:
	virtual void BeginPlay() override;

private:
	void SetCharacterMesh();
};
