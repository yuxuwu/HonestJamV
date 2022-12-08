// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Comp_MeleeWeapon.generated.h"

class UBoxComponent;
class AHonestJamVCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBlock);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishAttack);


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HONESTJAMV_API UComp_MeleeWeapon : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UComp_MeleeWeapon();

	UPROPERTY(BlueprintAssignable, Category = "Attacking")
	FOnAttack OnAttack;

	UPROPERTY(BlueprintAssignable, Category = "Attacking")
	FOnBlock OnBlock;

	UPROPERTY(BlueprintAssignable, Category = "Attacking")
	FOnFinishAttack OnFinishAttack;
	
	/** Box Component that acts as the hit for the weapon*/
	UPROPERTY(EditDefaultsOnly, Category = WeaponMesh)
	UBoxComponent* WeaponHitBoxComponent;

	/** Attaches weapon to the character */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void AttachWeapon(AHonestJamVCharacter* TargetCharacter);

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* AttackAnimation;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* BlockAnimation;

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

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* BlockAction;

	/** Make the weapon attack and swing weapon */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Block();

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AHonestJamVCharacter* Character;
private:
	UPROPERTY(EditAnywhere)
	FName WeaponSocketName;

};
