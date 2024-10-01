// Fill out your copyright notice in the Description page of Project Settings.


#include "InstallItemActor.h"
#include "Engine/StaticMesh.h"
#include "../../Actor/Interact/InstallPlaceInteractActor.h"
#include "../../Character/Player/PlayerCharacter.h"
#include "../../Component/ItemComponent/ItemComponent.h"

AInstallItemActor::AInstallItemActor()
{
    ItemComponent = CreateDefaultSubobject<UItemComponent>("ItemComponent");

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MInstall(TEXT("/Game/Sky_Dungeon/materials/props_materials/M_InstallObject.M_InstallObject"));

    if (MInstall.Succeeded())
        InstallMaterial = MInstall.Object;
}

bool AInstallItemActor::CanBePlaced(FVector const& Location)
{
    FHitResult HitResult;
    FVector Start = Location + FVector(0, 0, 50);
    FVector End = Location - FVector(0, 0, 100);

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel1);

    if (HitResult.GetActor())
    {
        AInstallPlaceInteractActor* InteractActor = Cast<AInstallPlaceInteractActor>(HitResult.GetActor());
        if (InteractActor)
        {
            if (bHit && InteractActor->GetIsInstall())
                return true;
        }  
    }
    return false;
}

void AInstallItemActor::ShowPreview(FVector const& Location)
{
    UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(InstallMaterial, this);
    if (DynamicMaterial)
    {
        if (CanBePlaced(Location))
            DynamicMaterial->SetVectorParameterValue(FName("Color"), FLinearColor::Green);
        else
            DynamicMaterial->SetVectorParameterValue(FName("Color"), FLinearColor::Red);
        DynamicMaterial->SetScalarParameterValue(FName("Opacity"), 0.5f);

        GetStaticMesh()->SetMaterial(0, DynamicMaterial);
    }

    SetActorLocation(Location);
}

void AInstallItemActor::Place(FVector const& Location, FRotator const& Rotation)
{
    if (CanBePlaced(Location))
    {
        SetActorLocationAndRotation(Location, Rotation);
        ResetColor();

        GetStaticMesh()->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    }
}

void AInstallItemActor::SetItem(int32 _ID)
{
    Super::SetItem(_ID);

    BaseMaterial = GetStaticMesh()->GetMaterial(0);
}

void AInstallItemActor::ResetColor()
{
    if(BaseMaterial)
        GetStaticMesh()->SetMaterial(0, BaseMaterial);
}