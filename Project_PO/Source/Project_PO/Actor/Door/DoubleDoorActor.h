// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDoorActor.h"
#include "DoubleDoorActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API ADoubleDoorActor : public ABaseDoorActor
{
	GENERATED_BODY()
	
public:
	ADoubleDoorActor();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* RightMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* LeftMesh;

	FRotator RightInitialRotation;
	FRotator RightTargetRotation;

	FRotator LeftInitialRotation;
	FRotator LeftTargetRotation;

protected:
	virtual void BeginPlay() override;

	virtual void OpenDoor(float Value) override;

public:
	class UStaticMeshComponent* GetRightMesh() { return RightMesh; }
	class UStaticMeshComponent* GetLeftMesh() { return LeftMesh; }
};
