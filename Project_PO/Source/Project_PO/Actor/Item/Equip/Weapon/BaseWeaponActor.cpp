// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponActor.h"
#include "../../../../AnimInstance/BaseGunAnimInstance.h"
#include "../../../../Character/Player/PlayerCharacter.h"
#include "../../../../Component/ItemComponent/EquipItemComponent.h"

ABaseWeaponActor::ABaseWeaponActor()
	: WeaponType(E_WeaponType::E_None)
{
	EquipType = E_EquipType::E_Weapon;
}

FVector ABaseWeaponActor::LineTraceFromCamera()
{
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);
    
    if (!GetOwner())
        return FVector();
    CollisionParams.AddIgnoredActor(GetOwner());

    APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(GetOwner());
    if (!OwnerCharacter)
        return FVector();

    APlayerController* PlayerController = Cast<APlayerController>(GetOwner()->GetInstigatorController());
    if (!PlayerController)
        return FVector();

    FVector CameraLocation;
    FRotator CameraRotation;

    PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

    FVector Start = CameraLocation;
    FVector End = Start + CameraRotation.Vector() * 2000.f;

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_GameTraceChannel3,
        CollisionParams
    );

    FVector HitValue;
    if (bHit)
        HitValue = HitResult.ImpactPoint;
    else
        HitValue = End;

    return HitValue;
}

void ABaseWeaponActor::SetItem(int32 _ID)
{
    AEquipItemActor::SetItem(_ID);

    if (ItemComponent)
    {
        UEquipItemComponent* EquipItemComponent = GetItemComponent<UEquipItemComponent>();
        if (EquipItemComponent)
        {
            GetSkeletalMesh()->SetAnimInstanceClass(EquipItemComponent->GetWeaponAnimInstance());
            AnimInstance = Cast<UBaseGunAnimInstance>(GetSkeletalMesh()->GetAnimInstance());
        }
    }
}