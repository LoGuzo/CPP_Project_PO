// Fill out your copyright notice in the Description page of Project Settings.


#include "OwlTeleportActor.h"
#include "LevelSequencePlayer.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/StaticMesh.h"
#include "../../Character/Player/PlayerCharacter.h"
#include "../../Controller/Player/BasePlayerController.h"
#include "../../GameMode/MyBaseGameMode.h"
#include "../../Widget/Interaction/OwlInteractionWidget.h"

// Sets default values
AOwlTeleportActor::AOwlTeleportActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetBoxComponent();
	SetActorMesh();
}

void AOwlTeleportActor::SetBoxComponent()
{
	GetBoxComponent()->SetBoxExtent(FVector(100.f, 100.f, 100.f));
}

void AOwlTeleportActor::SetActorMesh()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (Mesh)
	{
		Mesh->SetupAttachment(RootComponent);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> ActorMesh(TEXT("/Game/Sky_Dungeon/meshes/props/SM_statue_02.SM_statue_02"));
		if (ActorMesh.Succeeded())
			Mesh->SetStaticMesh(ActorMesh.Object);
	}
}

void AOwlTeleportActor::SetLevelSequence()
{
	if (HasAuthority())
	{
		AMyBaseGameMode* GameMode = Cast<AMyBaseGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->PlaySequence(8001);

			FTimerHandle Timer;
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &AOwlTeleportActor::Teleport, 2.f, false);
		}
	}
}


void AOwlTeleportActor::Interact(AActor* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		if (CheckingRequiredItem(PlayerCharacter))
		{
			SetLevelSequence();
		}
	}
}

void AOwlTeleportActor::Teleport()
{
	if (HasAuthority())
	{
		AMyBaseGameMode* GameMode = Cast<AMyBaseGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->PlayBackGound(SoundName);

			TArray<class ABasePlayerController*> PlayerControllers = GameMode->GetPlayerControllers();
			for (ABasePlayerController* PlayerController : PlayerControllers)
			{
				PlayerController->GetPawn()->SetActorLocation(TeleportLocation);
			}
		}
	}
}