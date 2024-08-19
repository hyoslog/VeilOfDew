// Default
#include "VODPlayerState.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "AbilitySystem/VODAbilitySet.h"
#include "AbilitySystem/VODAbilitySystemComponent.h"

// Project-specific

// Local

AVODPlayerState::AVODPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UVODAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	check(AbilitySystemComponent);
}

void AVODPlayerState::ApplyAbilitySets(const TArray<UVODAbilitySet*>& InAbilitySets) const
{
	check(HasAuthority());
	check(AbilitySystemComponent);

	for (const UVODAbilitySet* const AbilitySet : InAbilitySets)
	{
		if (ensure(IsValid(AbilitySet)))
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr, nullptr);
		}
	}
}
