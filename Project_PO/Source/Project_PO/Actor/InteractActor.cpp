// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/StaticMesh.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Widget/Interaction/OwlInteractionWidget.h"

// Sets default values
AInteractActor::AInteractActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetBoxComponent();
	SetWidgetComponent();
}

// Called when the game starts or when spawned
void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetOwlInteraction();
}

void AInteractActor::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		PlayerCharacter->SetInteractActer(this);
		if (OwlInteractionWidget)
			OwlInteractionWidget->SetRenderOpacity(1.f);
	}
}

void AInteractActor::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		PlayerCharacter->SetInteractActer(nullptr);
		if (OwlInteractionWidget)
			OwlInteractionWidget->SetRenderOpacity(0.f);
	}
}

void AInteractActor::SetBoxComponent()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(200.0f, 100.0f, 100.0f));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AInteractActor::BeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AInteractActor::EndOverlap);
	RootComponent = BoxCollision;
}

void AInteractActor::SetWidgetComponent()
{
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction"));
	if (InteractionWidget)
	{
		InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
		InteractionWidget->SetupAttachment(RootComponent);
		InteractionWidget->SetDrawSize(FVector2D(100.f, 100.f));

		static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("/Game/ThirdPerson/Blueprints/Widget/Interaction/BP_OwlInteractionWidget.BP_OwlInteractionWidget_C"));
		if (UW.Succeeded())
		{
			InteractionWidget->SetWidgetClass(UW.Class);
		}
	}
}

void AInteractActor::SetOwlInteraction()
{
	if (InteractionWidget)
	{
		InteractionWidget->InitWidget();

		OwlInteractionWidget = Cast<UOwlInteractionWidget>(InteractionWidget->GetUserWidgetObject());
		if (OwlInteractionWidget)
		{
			OwlInteractionWidget->SetRenderOpacity(0.f);
			OwlInteractionWidget->SetTextContent(TEXT("F"));
		}
	}
}

void AInteractActor::Interact(APlayerCharacter* PlayerCharacter)
{
}
