#pragma once

// Default

// C++ Standard Library

// Third-party Library

// Unreal Engine

// Project-specific

// Local
#include "VODGameplayAbility.h"

// Last
#include "VODGameplayAbility_Sprint.generated.h"

UCLASS(Abstract)
class VEILOFDEW_API UVODGameplayAbility_Sprint final : public UVODGameplayAbility
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
