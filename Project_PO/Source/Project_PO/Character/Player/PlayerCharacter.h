// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
#include "../BaseCharacter.h"
#include "../../MyEnumClass.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	// TakeDamage
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	// Tick
	virtual void Tick(float DeltaTime) override;

	virtual void Jump() override;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	/** Aiming Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimingAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	/** Skill Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* UseSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InvenAction;

private:
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* CameraTimeline;

	UPROPERTY(VisibleAnywhere)
	FOnTimelineFloat InterpFunction;

	UPROPERTY(VisibleAnywhere)
	class UCurveFloat* CameraCurve;

	E_WeaponType WeaponType;

protected:
	FVector InitailZoomLocation;
	FVector TargetZoomLocation;

	float InitalSpringLength;
	float TargetSpringLength;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (AllowPrivateAccess = "true"))
	bool bIsAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (AllowPrivateAccess = "true"))
	bool bIsArmed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (AllowPrivateAccess = "true"))
	bool bIsSprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (AllowPrivateAccess = "true"))
	bool bIsMoveFront;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (AllowPrivateAccess = "true"))
	bool bIsFirstPlayer;

	UPROPERTY()
	class UBasePlayerAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere)
	class UInteractionComponent* InteractionComponent;
	UPROPERTY(VisibleAnywhere)
	class UEquipComponent* EquipComponent;
	UPROPERTY(VisibleAnywhere)
	class UInventoryComponent* InventoryComponent;
	UPROPERTY(VisibleAnywhere)
	class UPotionQuickSlotComponent* PotionQuickSlotComponent;

	UPROPERTY()
	class AActor* InteractActor;

	UPROPERTY()
	TMap<E_WeaponType, FString> AttackMontageMap;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for Interact input */
	void Interact(const FInputActionValue& Value);

	/** Called for Aiming input */
	void TriggeredAiming(const FInputActionValue& Value);
	void CanceledAiming(const FInputActionValue& Value);
	void CompletedAiming(const FInputActionValue& Value);

	/** Called for Sprint input */
	void TriggeredSprint(const FInputActionValue& Value);
	void CanceledSprint(const FInputActionValue& Value);
	void CompletedSprint(const FInputActionValue& Value);

	/** Called for Attack input */
	void Attack(const FInputActionValue& Value);

	/** Called for Attack input */
	void UseSkill(const FInputActionValue& Value);

	/** Called for Attack input */
	void ShowInven(const FInputActionValue& Value);

private:
	void BindInputAction();

	void SetupCurve();
	void SetupCameraCurve();

	UFUNCTION()
	void Zoom(float Value);
	void SetupCamera();

	void SetupStatComponent();
	void SetupInventoryComponent();

	void DisplayCrosshair();

	void AttackMontage();

public:
	UPROPERTY(EditAnywhere)
	FVector JointTargetLocation;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void SetInteractActor(class AActor* _InteractActor) { InteractActor = _InteractActor; }

	bool GetIsArmed() { return bIsArmed; }
	void SetIsArmed(bool _bIsArmed) { bIsArmed = _bIsArmed; }

	bool GetIsAiming() { return bIsAiming; }
	void SetIsAiming(bool _bIsAiming) { bIsAiming = _bIsAiming; }

	bool GetIsSprint() { return bIsSprint; }
	void SetIsSprint(bool _bIsSprint) { bIsSprint = _bIsSprint; }

	bool GetIsFirstPlayer() { return bIsFirstPlayer; }
	void SetIsFirstPlayer(bool _bIsFirstPlayer) { bIsFirstPlayer = _bIsFirstPlayer; }

	E_WeaponType GetWeaponType() { return WeaponType; }
	void SetWeaponType(E_WeaponType _WeaponType) { WeaponType = _WeaponType; }

	class UEquipComponent* GetEquipComponent(){ return EquipComponent; }
	class UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }
	class UInteractionComponent* GetInteractionComponent() { return InteractionComponent; }

	//FTransform GetLeftHandSocketTransform();

	virtual void ShotAttackCheck() override;

	virtual void Died() override;

public:
	void SetEquip(int32 ID);

	void AttackCheck();
};
