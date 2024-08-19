#pragma once

// Default

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "GameFramework/GameModeBase.h"

// Project-specific

// Local

// Last
#include "VODGameMode.generated.h"

UCLASS(minimalapi)
class AVODGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void OnPostLogin(AController* NewPlayer) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	TObjectPtr<const class UVODPawnData> DefaultPawnData;
};



