#pragma once

// Default

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "GameFramework/PlayerController.h"

// Project-specific

// Local
#include "VODPlayerState.h"

// Last
#include "VODPlayerController.generated.h"

UCLASS()
class VEILOFDEW_API AVODPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	inline class AVODPlayerState* GetPlayerState() const { return Cast<AVODPlayerState>(PlayerState); }

public:
	class UVODAbilitySystemComponent* GetAbilitySystemComponent() const;

protected:
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused);
};