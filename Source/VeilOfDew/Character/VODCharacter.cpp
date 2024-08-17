// Default
#include "VODCharacter.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"

// Project-specific
#include "AbilitySystem/Attributes/VODAttributeSet_Character.h"
#include "AbilitySystem/VODAbilitySystemComponent.h"

// Local

AVODCharacter::AVODCharacter()
{
	check(RootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	check(SpringArmComponent);
	SpringArmComponent->SetupAttachment(RootComponent);

	FollowCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraComponent"));
	check(FollowCameraComponent);
	FollowCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	AbilitySystemComponent = CreateDefaultSubobject<UVODAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	check(AbilitySystemComponent);

	CharacterSet = CreateDefaultSubobject<UVODAttributeSet_Character>(TEXT("CharacterSet"));	
	check(CharacterSet);
}

void AVODCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(CharacterSet);

	auto* CharMovement = GetCharacterMovement();
	check(CharMovement);
	CharMovement->MaxWalkSpeed *= CharacterSet->GetMoveSpeedRate();
}

void AVODCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AbilitySystemComponent = nullptr;
	CharacterSet = nullptr;
}

void AVODCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* const PlayerController = Cast<APlayerController>(GetController());
	if (IsValid(PlayerController) == false)
	{
		ensure(false);
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (IsValid(EnhancedInputSubsystem) == false)
	{
		ensure(false);
		return;
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent) == false)
	{
		ensure(false);
		return;
	}

	EnhancedInputSubsystem->AddMappingContext(DefaultMappingContext, 0);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVODCharacter::Move);

	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVODCharacter::Look);

	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &AVODCharacter::Run);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AVODCharacter::StopRun);
}

void AVODCharacter::Move(const FInputActionValue& InValue)
{
	const auto* const CharacterController = GetController();
	if (IsValid(CharacterController) == false)
	{
		ensure(false);
		return;
	}

	const FVector2D MovementVector = InValue.Get<FVector2D>();

	// find out which way is forward
	const FRotator Rotation = CharacterController->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AVODCharacter::Look(const FInputActionValue& InValue)
{
	const FVector2D LookAxisVector = InValue.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AVODCharacter::Run()
{
}

void AVODCharacter::StopRun()
{
}
