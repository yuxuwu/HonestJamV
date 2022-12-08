// Fill out your copyright notice in the Description page of Project Settings.


#include "Comp_Crossbow.h"
#include "HonestJamV/HonestJamVCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "HonestJamV/HonestJamVCharacter.h"

void UComp_Crossbow::AttachWeapon(AHonestJamVCharacter* TargetCharacter)
{
	Super::AttachWeapon(TargetCharacter);
	Character->SetHasMeleeWeapon(false);
	Character->SetHasCrossbow(true);
}

void UComp_Crossbow::Attack()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}
	// Try and play a firing animation if specified
	if (AttackAnimation != nullptr && Character->bCanShoot)
	{
		if (AttackSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, AttackSound, Character->GetActorLocation());
		}
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr && !AnimInstance->Montage_IsPlaying(AttackAnimation) && !Character->GetIsReloading())
		{
			AnimInstance->Montage_Play(AttackAnimation, 1.f);
		}
		OnAttack.Broadcast();

		Character->SetCanShoot(false);
	}
}