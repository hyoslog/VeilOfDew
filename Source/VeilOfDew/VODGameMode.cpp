// Copyright Epic Games, Inc. All Rights Reserved.

#include "VODGameMode.h"
#include "VODCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVODGameMode::AVODGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
