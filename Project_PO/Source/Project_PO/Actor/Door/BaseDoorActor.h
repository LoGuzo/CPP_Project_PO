// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractActor.h"
#include "Components/TimelineComponent.h"
#include "BaseDoorActor.generated.h"


UENUM(BlueprintType)
enum class E_DoorType : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_Single UMETA(DisplayName = "Single"),
	E_Double UMETA(DisplayName = "Double"),
};

UCLASS()
class PROJECT_PO_API ABaseDoorActor : public AInteractActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseDoorActor();

private:
	bool bIsOpened;

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DoorTimeline;

	FOnTimelineFloat InterpFunction;

	UPROPERTY()
	class UCurveFloat* DoorCurve;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Type, meta = (AllowPrivateAccess = "true"))
	E_DoorType DoorType;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OpenDoor(float Value) {};

public:
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;
};
