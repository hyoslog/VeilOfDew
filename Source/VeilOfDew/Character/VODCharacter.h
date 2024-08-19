#pragma once

// Default
#include "CoreMinimal.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

// Project-specific

// Local

// Last
#include "VODCharacter.generated.h"

UCLASS(config=Game)
class AVODCharacter : public ACharacter
{
	GENERATED_BODY()	

public:
	AVODCharacter();

public:
	inline class USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
	inline class UCameraComponent* GetFollowCamera() const { return FollowCameraComponent; }

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	

protected:
	void Move(const struct FInputActionValue& InValue);

	void Look(const struct FInputActionValue& InValue);

	void Run();
	void StopRun();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class UCameraComponent> FollowCameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<const class UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<const class UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<const class UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<const class UInputAction> RunAction;
};