#pragma once

// Default

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "GameFramework/PlayerState.h"

// Project-specific

// Local

// Last
#include "VODPlayerState.generated.h"

UCLASS()
class VEILOFDEW_API AVODPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AVODPlayerState();

public:
	inline class UVODAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }

public:
	void ApplyAbilitySets(const TArray<class UVODAbilitySet*>& InAbilitySets) const;

private:
	UPROPERTY(Transient)
	TObjectPtr<class UVODAbilitySystemComponent> AbilitySystemComponent;
};