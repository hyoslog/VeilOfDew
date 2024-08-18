#pragma once

// Default
#include "CoreMinimal.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "AbilitySystemComponent.h"

// Project-specific

// Local
#include "VODAttributeSet.h"

// Last
#include "VODAttributeSet_Character.generated.h"

UCLASS()
class VEILOFDEW_API UVODAttributeSet_Character : public UVODAttributeSet
{
	GENERATED_BODY()

private:
	UVODAttributeSet_Character();

public:
	VOD_ATTRIBUTE_ACCESSORS(UVODAttributeSet_Character, MoveSpeedRate)

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MoveSpeedRate;	
};
