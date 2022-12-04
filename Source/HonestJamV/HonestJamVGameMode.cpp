// Copyright Epic Games, Inc. All Rights Reserved.

#include "HonestJamVGameMode.h"
#include "HonestJamVCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHonestJamVGameMode::AHonestJamVGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
