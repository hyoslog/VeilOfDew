#pragma once

// Default
#include "CoreMinimal.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "Engine/DataAsset.h"

// Project-specific

// Local

// Last
#include "VODPawnData.generated.h"

UCLASS(BlueprintType, Const)
class VEILOFDEW_API UVODPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Ability")
	TArray<TObjectPtr<class UVODAbilitySet>> AbilitySets;
};