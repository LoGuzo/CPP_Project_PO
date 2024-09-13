// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/Interactable.h"
#include "InteractActor.generated.h"

UCLASS()
class PROJECT_PO_API AInteractActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

private:
	UPROPERTY()
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* InteractionWidget;

	UPROPERTY()
	class UOwlInteractionWidget* OwlInteractionWidget;

private:
	void SetBoxComponent();
	void SetWidgetComponent();
	void SetOwlInteraction();

	UFUNCTION()
	void BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	class UBoxComponent* GetBoxComponent() { return BoxCollision; }
	class UWidgetComponent* GetInteractionWidget() { return InteractionWidget; }
};
