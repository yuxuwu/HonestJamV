// Fill out your copyright notice in the Description page of Project Settings.


#include "Comp_MeleeWeapon.h"
#include "Components/BoxComponent.h"
#include "HonestJamV/HonestJamVCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

UComp_MeleeWeapon::UComp_MeleeWeapon()
{

}

void UComp_MeleeWeapon::AttachWeapon(AHonestJamVCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr)
	{
		return;
	}
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, WeaponSocketName);

	Character->SetHasMeleeWeapon(true);

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(AttackMappingContext, 1);
		}
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Attack
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &UComp_MeleeWeapon::Attack);
		}
	}
}

void UComp_MeleeWeapon::Attack()
{
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Attack Function Ran"));

	// Try and play the sound if specified
	if (AttackSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, AttackSound, Character->GetActorLocation());
	}

	// Try and play a firing animation if specified
	if (AttackAnimation != nullptr && AttackAnimation)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr && !AnimInstance->Montage_IsPlaying(AttackAnimation))
		{
			AnimInstance->Montage_Play(AttackAnimation, 1.f);
		}
	}

	// Notify that the actor is being picked up
	OnAttack.Broadcast();
}

void UComp_MeleeWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(AttackMappingContext);
		}
	}

}
