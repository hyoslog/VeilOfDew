﻿#pragma once

// Default
#include "CoreMinimal.h"

// C++ Standard Library

// Third-party Library

// Unreal Engine
#include "AttributeSet.h"
#include "GameplayTagContainer.h"

// Project-specific

// Local

// Last
#include "VODAbilitySet.generated.h"

USTRUCT(BlueprintType)
struct FGameplayAbilityData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UVODGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FGameplayEffectData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> GameplayEffect;

	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};

USTRUCT(BlueprintType)
struct FGameplayAttributeSetData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeSet> AttributeSet;
};

USTRUCT(BlueprintType)
struct FAbilitySet_Handle
{
	GENERATED_BODY()

public:
	void AddAbilitySpecHandle(const struct FGameplayAbilitySpecHandle& InHandle);
	void AddGameplayEffectHandle(const struct FActiveGameplayEffectHandle& InHandle);
	void AddAttributeSet(class UAttributeSet* InSet);

	void TakeFromAbilitySystem(class UVODAbilitySystemComponent* InASC);

public:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> AttributeSets;
};

UCLASS(BlueprintType, Const)
class VEILOFDEW_API UVODAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	void GiveToAbilitySystem(class UVODAbilitySystemComponent* InASC, FAbilitySet_Handle* InHandle, UObject* InSourceObject) const;

private:
	void ApplyGameplayAbilityDatas(class UVODAbilitySystemComponent* InASC, FAbilitySet_Handle* InHandle, UObject* InSourceObject) const;
	void ApplyGameplayEffectDatas(class UVODAbilitySystemComponent* InASC, FAbilitySet_Handle* InHandle) const;
	void ApplyAttributeSetDatas(class UVODAbilitySystemComponent* InASC, FAbilitySet_Handle* InHandle) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TArray<FGameplayAbilityData> GameplayAbilityDatas;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TArray<FGameplayEffectData> GameplayEffectDatas;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TArray<FGameplayAttributeSetData> AttributeSetDatas;
};
