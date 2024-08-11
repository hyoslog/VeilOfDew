// Default
#include "VODAbilitySet.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine

// Project-specific
#include "AbilitySystem/Abilities/VODGamePlayAbility.h"
#include "AbilitySystem/VODAbilitySystemComponent.h"

// Local

void FVODAbilitySet_Handle::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& InHandle)
{
	if (ensure(InHandle.IsValid()))
	{
		AbilitySpecHandles.Add(InHandle);
	}
}

void FVODAbilitySet_Handle::AddGameplayEffectHandle(const FActiveGameplayEffectHandle& InHandle)
{
	if (ensure(InHandle.IsValid()))
	{
		GameplayEffectHandles.Add(InHandle);
	}
}

void FVODAbilitySet_Handle::AddAttributeSet(UAttributeSet* InSet)
{
	AttributeSets.Add(InSet);
}

void FVODAbilitySet_Handle::TakeFromAbilitySystem(UVODAbilitySystemComponent* InASC)
{
	check(InASC);

	if (InASC->IsOwnerActorAuthoritative() == false)
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			InASC->ClearAbility(Handle);
		}
	}

	for (const FActiveGameplayEffectHandle& Handle : GameplayEffectHandles)
	{
		if (Handle.IsValid())
		{
			InASC->RemoveActiveGameplayEffect(Handle);
		}
	}

	for (UAttributeSet* Set : AttributeSets)
	{
		InASC->RemoveSpawnedAttribute(Set);
	}

	AbilitySpecHandles.Reset();
	GameplayEffectHandles.Reset();
	AttributeSets.Reset();
}

void UVODAbilitySet::GiveToAbilitySystem(UVODAbilitySystemComponent* InASC, FVODAbilitySet_Handle* InHandle, UObject* InSourceObject) const
{
	check(InASC);

	if (InASC->IsOwnerActorAuthoritative() == false)
	{
		return;
	}

	ApplyGameplayAbilityDatas(InASC, InHandle, InSourceObject);
	ApplyGameplayEffectDatas(InASC, InHandle);
	ApplyAttributeSetDatas(InASC, InHandle);
}

void UVODAbilitySet::ApplyGameplayAbilityDatas(UVODAbilitySystemComponent* InASC, FVODAbilitySet_Handle* InHandle, UObject* InSourceObject) const
{
	for (const auto& AbilityData : GameplayAbilityDatas)
	{
		if (IsValid(AbilityData.Ability) == false)
		{
			ensure(false);
			continue;
		}

		auto* AbilityCDO = AbilityData.Ability->GetDefaultObject<UVODGameplayAbility>();
		check(AbilityCDO);

		FGameplayAbilitySpec AbillitySpec(AbilityCDO, AbilityData.AbilityLevel);
		AbillitySpec.SourceObject = InSourceObject;
		AbillitySpec.DynamicAbilityTags.AddTag(AbilityData.InputTag);

		const FGameplayAbilitySpecHandle AbilitySpecHandle = InASC->GiveAbility(AbillitySpec);

		if (InHandle != nullptr)
		{
			InHandle->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}
}

void UVODAbilitySet::ApplyGameplayEffectDatas(class UVODAbilitySystemComponent* InASC, FVODAbilitySet_Handle* InHandle) const
{
	for (const auto& EffectData : GameplayEffectDatas)
	{
		if (IsValid(EffectData.GameplayEffect) == false)
		{
			ensure(false);
			continue;
		}

		const auto* const GameplayEffectCDO = EffectData.GameplayEffect->GetDefaultObject<UGameplayEffect>();
		check(GameplayEffectCDO);

		const FActiveGameplayEffectHandle GameplayEffectHandle = InASC->ApplyGameplayEffectToSelf(GameplayEffectCDO, EffectData.EffectLevel, InASC->MakeEffectContext());

		if (InHandle != nullptr)
		{
			InHandle->AddGameplayEffectHandle(GameplayEffectHandle);
		}
	}
}

void UVODAbilitySet::ApplyAttributeSetDatas(class UVODAbilitySystemComponent* InASC, FVODAbilitySet_Handle* InHandle) const
{
	for (const auto& SetData : AttributeSetDatas)
	{
		if (IsValid(SetData.AttributeSet) == false)
		{
			ensure(false);
			continue;
		}

		auto* NewSet = NewObject<UAttributeSet>(InASC->GetOwner(), SetData.AttributeSet);
		check(NewSet);

		InASC->AddAttributeSetSubobject(NewSet);

		if (InHandle != nullptr)
		{
			InHandle->AddAttributeSet(NewSet);
		}
	}
}