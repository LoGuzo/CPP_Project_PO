// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Interface/Interactable.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/WidgetManager.h"
#include "../Widget/Interaction/OwlInteractionWidget.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
	: InteractionRange(200.f)
	, bIsWidgetVisible(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>Widget(TEXT("/Game/ThirdPerson/Blueprints/Widget/Interaction/BP_OwlInteractionWidget.BP_OwlInteractionWidget_C"));
	if (Widget.Succeeded())
		InteractWidget = Widget.Class;
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	auto MyGameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (InteractWidget)
		{
			UWidgetManager* WidgetManager = MyGameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
			if (WidgetManager)
				WidgetManager->CreateAndAddWidget<UOwlInteractionWidget>(GetWorld(), TEXT("Interaction"), InteractWidget);
		}
	}
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckInteraction();
}

void UInteractionComponent::CheckInteraction()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (PlayerCharacter)
	{
		AActor* PotentialInteractActor = GetInteractableInRange();
		if (PotentialInteractActor)
		{
			if (!bIsWidgetVisible)
			{
				PlayerCharacter->SetInteractActor(PotentialInteractActor);
				ShowAndHideInteractWidget();
				bIsWidgetVisible = true;
			}
		}
		else
		{
			if (bIsWidgetVisible)
			{
				PlayerCharacter->SetInteractActor(nullptr);
				ShowAndHideInteractWidget();
				bIsWidgetVisible = false;
			}
		}
	}
}

void UInteractionComponent::ShowAndHideInteractWidget()
{
	auto MyGameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		UWidgetManager* WidgetManager = MyGameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
		if (WidgetManager)
		{
			UBaseUserWidget* NowWidget = WidgetManager->GetWidget<UBaseUserWidget>(TEXT("Interaction"));
			if (NowWidget)
				NowWidget->SetAddRemove();
		}
	}
}

AActor* UInteractionComponent::GetInteractableInRange()
{
	ACharacter* Player = Cast<ACharacter>(GetOwner());
	if (!Player)
		return nullptr;

	APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());
	if (!PlayerController)
		return nullptr;

	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector Offset = CameraRotation.Vector() * 200.0f;
	CameraLocation = CameraLocation + Offset;

	FVector End = CameraLocation + (CameraRotation.Vector() * InteractionRange);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, End, ECC_GameTraceChannel1, Params);

	if (bHit && HitResult.GetActor())
		return HitResult.GetActor();

	return nullptr;
}


