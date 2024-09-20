// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShotgunWeaponActor.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../../Character/Player/PlayerCharacter.h"
#include "../../../../../Component/ItemComponent/EquipItemComponent.h"
#include "../../../../../Widget/Etc/CrosshairEtcWidget.h"

ABaseShotgunWeaponActor::ABaseShotgunWeaponActor()
{
	WeaponType = E_WeaponType::E_Shotgun;

	static ConstructorHelpers::FClassFinder<UCrosshairEtcWidget> Crosshair(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/BP_ShotgunCrosshair.BP_ShotgunCrosshair_C"));
	if (Crosshair.Succeeded())
		CrosshairWidget = Crosshair.Class;
}

void ABaseShotgunWeaponActor::Fire()
{
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    if (!GetOwner())
        return;
    CollisionParams.AddIgnoredActor(GetOwner());

    APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(GetOwner());
    if (!OwnerCharacter)
        return;

    FVector HitVector = LineTraceFromCamera();

    FVector Start = GetSkeletalMesh()->GetSocketLocation(TEXT("Muzzle"));

    FVector Direction = (HitVector - Start).GetSafeNormal();

    float SpreadAngle = 5.f;
    int32 NumPellets = 9;

    for (int32 i = 0; i < NumPellets; i++)
    {
        FRotator SpreadRotation = Direction.Rotation();
        SpreadRotation.Pitch += FMath::RandRange(-SpreadAngle, SpreadAngle);
        SpreadRotation.Yaw += FMath::RandRange(-SpreadAngle, SpreadAngle);
        FVector TargetDirection = SpreadRotation.Vector();
        FVector End = Start + (SpreadRotation.Vector() * 2000.0f);

        FHitResult HitResult;
        bool bHit = GetWorld()->LineTraceSingleByChannel(
            HitResult,
            Start,
            End,
            ECC_GameTraceChannel3,
            CollisionParams
        );

        if (bHit)
        {
            // 적을 타격한 경우
            FHitResult ObstacleHitResult;
            bool bObstacleHit = GetWorld()->LineTraceSingleByChannel(
                ObstacleHitResult,
                Start,
                HitResult.ImpactPoint,
                ECC_Visibility,
                CollisionParams
            );

            if (bObstacleHit)
                DrawDebugLine(GetWorld(), Start, ObstacleHitResult.ImpactPoint, FColor::Red, false, 1.f, 0, 1.0f);
            else
            {
                UGameplayStatics::ApplyPointDamage(
                    HitResult.GetActor(),
                    GetItemComponent<UEquipItemComponent>()->GetAttackPower(),
                    TargetDirection, HitResult,
                    OwnerCharacter->GetController(),
                    this, UDamageType::StaticClass()
                );
                DrawDebugLine(GetWorld(), Start, HitResult.ImpactPoint, FColor::Green, false, 5.f, 0, 1.0f);
            }
        }
    }
}