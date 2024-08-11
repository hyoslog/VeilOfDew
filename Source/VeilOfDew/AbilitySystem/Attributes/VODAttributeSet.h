#pragma once

// Default
#include "CoreMinimal.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "AttributeSet.h"

// Project-specific

// Local

// Last
#include "VODAttributeSet.generated.h"

#define VOD_ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class VEILOFDEW_API UVODAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
};
