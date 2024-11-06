// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePistolWeaponActor.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../../AnimInstance/BaseGunAnimInstance.h"
#include "../../../../../Character/Player/PlayerCharacter.h"
#include "../../../../../Component/ItemComponent/EquipItemComponent.h"
#include "../../../../../Widget/Etc/CrosshairEtcWidget.h"

ABasePistolWeaponActor::ABasePistolWeaponActor()
{
	WeaponType = E_WeaponType::E_Rifle;

	static ConstructorHelpers::FClassFinder<UCrosshairEtcWidget> Crosshair(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/WBP_NormalCrosshair.WBP_NormalCrosshair_C"));
	if (Crosshair.Succeeded())
		CrosshairWidget = Crosshair.Class;
}

void ABasePistolWeaponActor::Fire()
{
	if (GetAnimInstance())
		GetAnimInstance()->OnGunAttackPlayAM();
	
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
	FVector TargetDirection = (HitVector - Start).GetSafeNormal();
	FVector End = Start + TargetDirection * 2000.f;

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
		if (!AttackHitResult.GetActor()->ActorHasTag("Enemy"))
			return;

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
			//DrawDebugLine(GetWorld(), Start, ObstacleHitResult.ImpactPoint, FColor::Red, false, 1.f, 0, 1.0f);
			return;
		}

		UGameplayStatics::ApplyPointDamage(
			AttackHitResult.GetActor(), 
			GetItemComponent<UEquipItemComponent>()->GetAttackPower(),
			TargetDirection, AttackHitResult,
			OwnerCharacter->GetController(),
			this, UDamageType::StaticClass()
		);
		//DrawDebugLine(GetWorld(), Start, AttackHitResult.ImpactPoint, FColor::Green, false, 5.f, 0, 1.0f);
	}
}