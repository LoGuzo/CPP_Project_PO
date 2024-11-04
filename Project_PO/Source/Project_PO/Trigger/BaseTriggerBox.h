// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "BaseTriggerBox.generated.h"


UCLASS()
class PROJECT_PO_API ABaseTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	ABaseTriggerBox();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (AllowPrivateAccess = true))
	int32 ActiveCnt;
	int32 CurActiveCnt;

	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (AllowPrivateAccess = true))
	int32 SequenceID;

	UPROPERTY(EditAnywhere, Category = "Audio", meta = (AllowPrivateAccess = true))
	FString SoundName;

protected:
	UFUNCTION()
	virtual void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	virtual void SetUpTrigger() {};
	virtual void TearDownTrigger() {};

	virtual void SetLevelSequence() {};

protected:
	class ULevelSequencePlayer* GetPlaySequence(int32 const& _SequenceID);
	void AddRemoveWidget(FString const& WidgetName);
};
