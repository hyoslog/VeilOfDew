#pragma once

// Default
#include "CoreMinimal.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "Abilities/GameplayAbility.h"

// Project-specific

// Local

// Last
#include "VODGameplayAbility.generated.h"

/**
 * Ability 활성화 타이밍
 */
UENUM()
enum class EAbilityActivationTiming : uint8
{
	OnInputTriggered,	// 입력 발생 시 활성화
	WhileInputActive,	// 입력이 활성화된 동안 계속 활성화
	OnInitialized		// 활성화 상태로 시작
};

UCLASS()
class VEILOFDEW_API UVODGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	inline EAbilityActivationTiming GetActivationTiming() const { return ActivationTiming; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AbilityActivation")
	EAbilityActivationTiming ActivationTiming = EAbilityActivationTiming::OnInputTriggered;
};
