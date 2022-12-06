// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Comp_MeleeWeapon.generated.h"

class UBoxComponent;
class AHonestJamVCharacter;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HONESTJAMV_API UComp_MeleeWeapon : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UComp_MeleeWeapon();

	/** Box Component that acts as the hit for the weapon*/
	UPROPERTY(EditDefaultsOnly, Category = WeaponMesh)
	UBoxComponent* WeaponHitBoxComponent;

	/** Attaches weapon to the character */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeapon(AHonestJamVCharacter* TargetCharacter);

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* AttackAnimation;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* AttackSound;

	/** Make the weapon attack and swing weapon */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Attack();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* AttackMappingContext;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	AHonestJamVCharacter* Character;
};
