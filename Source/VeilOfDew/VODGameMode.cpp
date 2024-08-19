// Default
#include "VODGameMode.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "GameFramework/Controller.h"

// Project-specific
#include "Pawn/VODPawnData.h"
#include "Player/VODPlayerState.h"

// Local

void AVODGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	check(NewPlayer);

	if (NewPlayer->HasAuthority())
	{
		const auto* const NewPlayerState = NewPlayer->GetPlayerState<AVODPlayerState>();
		if (ensure(IsValid(NewPlayerState)))
		{
			if (ensure(IsValid(DefaultPawnData)))
			{
				NewPlayerState->ApplyAbilitySets(DefaultPawnData->AbilitySets);
			}
		}
	}	
}
