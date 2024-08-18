#pragma once

// Default
#include "CoreMinimal.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "GameplayEffectExecutionCalculation.h"

// Project-specific

// Local

// Last
#include "VODMoveSpeedRateExecution.generated.h"

UCLASS(BlueprintType, Const)
class VEILOFDEW_API UVODMoveSpeedRateExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UVODMoveSpeedRateExecution();

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
