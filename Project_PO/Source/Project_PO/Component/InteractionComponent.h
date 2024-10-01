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
	bool bIsWidgetVisible;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	float InteractionRange;

	UPROPERTY()
	class AInstallItemActor* InstallItem;

	TSubclassOf<class UOwlInteractionWidget> InteractWidget;

private:
	AActor* GetInteractableInRange();
	void ShowAndHideInteractWidget();
	
	void CheckInteraction();

	void CheckInstall(FVector const& Location);

public:
	void SetInteractionRange(float _InteractionRange) { InteractionRange = _InteractionRange; }
	void SetInstallItem(class AInstallItemActor* _InstallItem) { InstallItem = _InstallItem; }
	void InstallObject(FVector const& Location, FRotator const& Rotation);
};
