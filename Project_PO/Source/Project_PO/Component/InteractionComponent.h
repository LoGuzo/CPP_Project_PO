// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Component/BaseActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PO_API UInteractionComponent : public UBaseActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	float InteractionRange;

	bool bIsWidgetVisible;

	TSubclassOf<class UOwlInteractionWidget> InteractWidget;

	UPROPERTY()
	class UOwlInteractionWidget* InteractUI;

private:
	AActor* GetInteractableInRange();

	void ShowAndHideInteractWidget();

	void CheckInteraction();

public:
	void SetInteractionRange(float _InteractionRange) { InteractionRange = _InteractionRange; }
};
