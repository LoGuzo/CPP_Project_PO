// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDoorActor.h"
#include "SingleDoorActor.generated.h"

UENUM(BlueprintType)
enum class E_DirectionType : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_Right UMETA(DisplayName = "Right"),
	E_Left UMETA(DisplayName = "Left"),
};

UCLASS()
class PROJECT_PO_API ASingleDoorActor : public ABaseDoorActor
{
	GENERATED_BODY()

public:
	ASingleDoorActor();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Type, meta = (AllowPrivateAccess = "true"))
	E_DirectionType DirectionType;

	FRotator InitialRotation;

	FRotator TargetRotation;

protected:
	virtual void BeginPlay() override;

	virtual void OpenDoor(float Value) override;

public:
	class UStaticMeshComponent* GetMesh() { return Mesh; }
};
