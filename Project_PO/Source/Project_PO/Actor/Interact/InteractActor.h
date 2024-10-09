// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractActor.generated.h"

UCLASS()
class PROJECT_PO_API AInteractActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractActor();

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 RequiredQuestID;

	UPROPERTY(VisibleAnywhere)
	int32 RequiredItemID;

private:
	void SetBoxComponent();

protected:
	bool CheckingRequiredQuest();
	bool CheckingRequiredItem(class AActor* PlayerCharacter);

public:
	class UBoxComponent* GetBoxComponent() { return BoxCollision; }
};
