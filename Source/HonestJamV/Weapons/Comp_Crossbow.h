// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Comp_MeleeWeapon.h"
#include "Comp_Crossbow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShoot);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HONESTJAMV_API UComp_Crossbow : public UComp_MeleeWeapon
{
	GENERATED_BODY()
	
public:
	virtual void AttachWeapon(AHonestJamVCharacter* TargetCharacter) override;
	virtual void Attack() override;

	UPROPERTY(BlueprintAssignable, Category = "Attacking")
	FOnShoot OnShoot;
};
