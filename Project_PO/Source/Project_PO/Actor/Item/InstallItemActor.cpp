// Fill out your copyright notice in the Description page of Project Settings.


#include "InstallItemActor.h"
#include "../../Actor/Interact/InteractActor.h"
#include "../../Character/Player/PlayerCharacter.h"
#include "../../Component/ItemComponent/ItemComponent.h"

AInstallItemActor::AInstallItemActor()
{
    ItemComponent = CreateDefaultSubobject<UItemComponent>("ItemComponent");
}

bool AInstallItemActor::CanBePlaced(FVector const& Location)
{
    FHitResult HitResult;
    FVector Start = Location + FVector(0, 0, 50);
    FVector End = Location - FVector(0, 0, 100);

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel1);

    if (HitResult.GetActor())
    {
        AInteractActor* InteractActor = Cast<AInteractActor>(HitResult.GetActor());
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
    UMaterialInterface* BaseMaterial = GetStaticMesh()->GetMaterial(0);
    UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
    if (DynamicMaterial)
    {
        if (CanBePlaced(Location))
            DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), FLinearColor::Green);
        else
            DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), FLinearColor::Red);
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
        ResetItem();
    }
}

void AInstallItemActor::SetItem(int32 _ID)
{
    Super::SetItem(_ID);

    UMaterialInterface* BaseMaterial = GetStaticMesh()->GetMaterial(0);
    UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
    if (DynamicMaterial)
        DynamicMaterial->GetVectorParameterValue(FName("BaseColor"), OriginalColor);
}

void AInstallItemActor::ResetColor()
{
    UMaterialInterface* BaseMaterial = GetStaticMesh()->GetMaterial(0);
    UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
    if (DynamicMaterial)
    {
        DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), OriginalColor);
        DynamicMaterial->SetScalarParameterValue(FName("Opacity"), 1.f);

        GetStaticMesh()->SetMaterial(0, DynamicMaterial);
    }
}