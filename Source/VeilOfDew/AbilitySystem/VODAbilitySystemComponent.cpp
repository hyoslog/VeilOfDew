// Default
#include "VODAbilitySystemComponent.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine

// Project-specific
#include "Abilities/VODGameplayAbility.h"

// Local

void UVODAbilitySystemComponent::ProcessAbilityInput()
{
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandlesToActivate;

	ProcessAbilityInput_Held(AbilitySpecHandlesToActivate);
	ProcessAbilityInput_Pressed(AbilitySpecHandlesToActivate);

	for (const auto& AbilitySpecHandle : AbilitySpecHandlesToActivate)
	{
		TryActivateAbility(AbilitySpecHandle);
	}

	ProcessAbilityInput_Released();
}

void UVODAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InInputTag)
{
	if (InInputTag.IsValid())
	{
		ensure(false);
		return;
	}

	for (const auto& AbilitySpec : ActivatableAbilities.Items)
	{
		if (IsValid(AbilitySpec.Ability) == false)
		{
			ensure(false);
			continue;
		}

		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))
		{
			InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
			InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
		}
	}
}

void UVODAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InInputTag)
{
	if (InInputTag.IsValid())
	{
		ensure(false);
		return;
	}

	for (const auto& AbilitySpec : ActivatableAbilities.Items)
	{
		if (IsValid(AbilitySpec.Ability) == false)
		{
			ensure(false);
			continue;
		}

		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))
		{
			InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
			InputHeldSpecHandles.Remove(AbilitySpec.Handle);
		}
	}
}

void UVODAbilitySystemComponent::ProcessAbilityInput_Held(TArray<FGameplayAbilitySpecHandle>& OutAbilitySpecHandlesToActivate)
{
	for (const auto& SpecHandle : InputHeldSpecHandles)
	{
		const auto* const AbilitySpec = FindAbilitySpecFromHandle(SpecHandle);
		if ((AbilitySpec == nullptr) || (IsValid(AbilitySpec->Ability) == false) || (AbilitySpec->Handle.IsValid() == false))
		{
			ensure(false);
			continue;
		}

		if (AbilitySpec->IsActive())
		{
			const auto* const AbilityCDO = Cast<UVODGameplayAbility>(AbilitySpec->Ability);

			if (AbilityCDO == nullptr)
			{
				ensure(false);
				continue;
			}

			if (AbilityCDO->GetActivationTiming() == EAbilityActivationTiming::WhileInputActive)
			{
				OutAbilitySpecHandlesToActivate.AddUnique(AbilitySpec->Handle);
			}
		}
	}

	InputHeldSpecHandles.Reset();
}

void UVODAbilitySystemComponent::ProcessAbilityInput_Pressed(TArray<FGameplayAbilitySpecHandle>& OutAbilitySpecHandlesToActivate)
{
	for (const auto& SpecHandle : InputPressedSpecHandles)
	{
		auto* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle);
		if ((AbilitySpec == nullptr) || (IsValid(AbilitySpec->Ability) == false) || (AbilitySpec->Handle.IsValid() == false))
		{
			ensure(false);
			continue;
		}

		AbilitySpec->InputPressed = true;

		if (AbilitySpec->IsActive())
		{
			AbilitySpecInputReleased(*AbilitySpec);
		}
		else
		{
			const auto* const AbilityCDO = Cast<UVODGameplayAbility>(AbilitySpec->Ability);

			if (AbilityCDO == nullptr)
			{
				ensure(false);
				continue;
			}

			if (AbilityCDO->GetActivationTiming() == EAbilityActivationTiming::OnInputTriggered)
			{
				OutAbilitySpecHandlesToActivate.AddUnique(AbilitySpec->Handle);
			}
		}
	}

	InputPressedSpecHandles.Reset();
}

void UVODAbilitySystemComponent::ProcessAbilityInput_Released()
{
	for (const auto& SpecHandle : InputReleasedSpecHandles)
	{
		auto* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle);
		if ((AbilitySpec == nullptr) || (IsValid(AbilitySpec->Ability) == false))
		{
			ensure(false);
			continue;
		}

		AbilitySpec->InputPressed = false;

		if (AbilitySpec->IsActive())
		{
			AbilitySpecInputReleased(*AbilitySpec);
		}
	}

	InputReleasedSpecHandles.Reset();
}
