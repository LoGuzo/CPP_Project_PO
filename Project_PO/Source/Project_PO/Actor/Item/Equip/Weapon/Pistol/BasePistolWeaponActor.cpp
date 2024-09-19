// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePistolWeaponActor.h"
#include "../../../../../Character/Player/PlayerCharacter.h"
#include "../../../../../Widget/Etc/CrosshairEtcWidget.h"

ABasePistolWeaponActor::ABasePistolWeaponActor()
{
	WeaponType = E_WeaponType::E_Rifle;

	static ConstructorHelpers::FClassFinder<UCrosshairEtcWidget> Crosshair(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/BP_NormalCrosshair.BP_NormalCrosshair_C"));
	if (Crosshair.Succeeded())
		CrosshairWidget = Crosshair.Class;
}

void ABasePistolWeaponActor::Fire()
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

	if (HitVector == InvalidLocation)
		return;

	FVector Start = GetSkeletalMesh()->GetSocketLocation(TEXT("Muzzle"));
	FVector End = Start + (LineTraceFromCamera() - Start).GetSafeNormal() * 2000.f;

	FHitResult AttackHitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		AttackHitResult,
		Start,
		End,
		ECC_GameTraceChannel3,
		CollisionParams
	);

	if (bHit)
	{
		FHitResult ObstacleHitResult;
		bool bObstacleHit = GetWorld()->LineTraceSingleByChannel(
			ObstacleHitResult,
			Start,
			AttackHitResult.ImpactPoint,
			ECC_Visibility,
			CollisionParams
		);
		if (bObstacleHit)
		{
			DrawDebugLine(GetWorld(), Start, ObstacleHitResult.ImpactPoint, FColor::Red, false, 1.f, 0, 1.0f);
			return;
		}

		DrawDebugLine(GetWorld(), Start, AttackHitResult.ImpactPoint, FColor::Green, false, 5.f, 0, 1.0f);
	}
}