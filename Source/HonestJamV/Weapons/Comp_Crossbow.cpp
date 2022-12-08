// Fill out your copyright notice in the Description page of Project Settings.


#include "Comp_Crossbow.h"
#include "HonestJamV/HonestJamVCharacter.h"

void UComp_Crossbow::AttachWeapon(AHonestJamVCharacter* TargetCharacter)
{
	Super::AttachWeapon(TargetCharacter);

	Character->SetHasCrossbow(true);
}
