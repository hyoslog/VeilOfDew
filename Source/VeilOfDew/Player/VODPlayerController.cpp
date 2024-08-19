// Default
#include "VODPlayerController.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine

// Project-specific
#include "AbilitySystem/VODAbilitySystemComponent.h"

// Local

UVODAbilitySystemComponent* AVODPlayerController::GetAbilitySystemComponent() const
{
	if (IsValid(GetPlayerState()) == false)
	{
		ensure(false);
		return nullptr;
	}

	return (GetPlayerState()->GetAbilitySystemComponent());
}

void AVODPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);

	auto* ASC = GetAbilitySystemComponent();
	if (ensure(IsValid(ASC)))
	{
		ASC->ProcessAbilityInput();
	}
}
