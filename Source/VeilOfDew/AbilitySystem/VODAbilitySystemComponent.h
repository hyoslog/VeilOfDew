#pragma once

// Default
#include "CoreMinimal.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "AbilitySystemComponent.h"

// Project-specific

// Local

// Last
#include "VODAbilitySystemComponent.generated.h"
UCLASS()
class VEILOFDEW_API UVODAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void ProcessAbilityInput();

protected:
	virtual void AbilityInputTagPressed(const FGameplayTag& InInputTag);
	virtual void AbilityInputTagReleased(const FGameplayTag& InInputTag);

	virtual void ProcessAbilityInput_Held(TArray<FGameplayAbilitySpecHandle>& OutAbilitySpecHandlesToActivate);
	virtual void ProcessAbilityInput_Pressed(TArray<FGameplayAbilitySpecHandle>& OutAbilitySpecHandlesToActivate);
	virtual void ProcessAbilityInput_Released();

protected:
	// Pressed 지속되는 동안 트리거
	UPROPERTY(Transient)
		TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;

	// Pressed 발생 시 트리거
	UPROPERTY(Transient)
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	// Released 발생 시 트리거
	UPROPERTY(Transient)
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;	
};
