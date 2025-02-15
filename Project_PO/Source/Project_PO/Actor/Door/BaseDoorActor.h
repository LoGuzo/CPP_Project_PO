// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "../Interact/InteractActor.h"
#include "../../Interface/Interactable.h"
#include "BaseDoorActor.generated.h"


UENUM(BlueprintType)
enum class E_DoorType : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_Single UMETA(DisplayName = "Single"),
	E_Double UMETA(DisplayName = "Double"),
};

UCLASS()
class PROJECT_PO_API ABaseDoorActor : public AInteractActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseDoorActor();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	bool bIsOpened;

private:
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DoorTimeline;

	FOnTimelineFloat InterpFunction;

	UPROPERTY()
	class UCurveFloat* DoorCurve;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Type", meta = (AllowPrivateAccess = "true"))
	E_DoorType DoorType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ParticleComponent;

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	UAudioComponent* AudioComponent;

protected:
	UFUNCTION()
	virtual void OpenDoor(float Value) {};

public:
	virtual void Interact(class AActor* PlayerCharacter) override;
};
