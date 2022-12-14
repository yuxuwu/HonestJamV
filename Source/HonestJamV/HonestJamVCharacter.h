// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "HonestJamVCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class UComp_MeleeWeapon;

UCLASS(config=Game)
class AHonestJamVCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	
public:
	AHonestJamVCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasCrossbow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasMeleeWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bIsReloading;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UComp_MeleeWeapon* Comp_MeleeWeapon;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	UComp_MeleeWeapon* GetComp_MeleeWeapon() { return Comp_MeleeWeapon; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetComp_MeleeWeapon(UComp_MeleeWeapon* NewComp_MeleeWeapon) { Comp_MeleeWeapon = NewComp_MeleeWeapon; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetIsReloading(bool bNewIsReloading) { bIsReloading = bNewIsReloading; }

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasCrossbow(bool bNewHasCrossbow) { bHasCrossbow = bNewHasCrossbow; }

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasMeleeWeapon(bool bNewHasMeleeWeapon);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetIsReloading() { return bIsReloading; }

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasCrossbow() { return bHasCrossbow; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasMeleeWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool bCanShoot = true;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetCanShoot() { return bCanShoot; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetCanShoot(bool NewCanShoot) { bCanShoot = NewCanShoot; }
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};

