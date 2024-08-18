// Default
#include "VODMoveSpeedRateExecution.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine

// Project-specific
#include "AbilitySystem/Attributes/VODAttributeSet_Character.h"

// Local

struct FMoveSpeedRateStatic
{
	FMoveSpeedRateStatic()
	{
		MoveSpeedRateDef.AttributeToCapture = UVODAttributeSet_Character::GetMoveSpeedRateAttribute();
		MoveSpeedRateDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
		MoveSpeedRateDef.bSnapshot = true;
	}

	FGameplayEffectAttributeCaptureDefinition MoveSpeedRateDef;
};

static FMoveSpeedRateStatic& GetMoveSpeedRateStatic()
{
	static FMoveSpeedRateStatic MoveSpeedRateStatic;
	return MoveSpeedRateStatic;
};

UVODMoveSpeedRateExecution::UVODMoveSpeedRateExecution()
{
	RelevantAttributesToCapture.Add(GetMoveSpeedRateStatic().MoveSpeedRateDef);
}

void UVODMoveSpeedRateExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// 적용할 MoveSpeedRate 값
	float MoveSpeedRateMagnitude = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetMoveSpeedRateStatic().MoveSpeedRateDef, EvaluateParameters, MoveSpeedRateMagnitude);

 	if (MoveSpeedRateMagnitude > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UVODAttributeSet_Character::GetMoveSpeedRateAttribute(), EGameplayModOp::Override, MoveSpeedRateMagnitude));
	}
}
