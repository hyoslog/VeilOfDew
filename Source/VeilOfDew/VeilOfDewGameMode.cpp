// Copyright Epic Games, Inc. All Rights Reserved.

#include "VeilOfDewGameMode.h"
#include "VeilOfDewCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVeilOfDewGameMode::AVeilOfDewGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
