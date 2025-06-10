// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RPGAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API URPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	//UAbilitySystemComponent는 Actor와 GAS사이의 연결 다리 역할을 한다.
	//예를 들어 밑에있는 AddCharcterAbilities함수를 호출하면 AbilitiesToGrant에 있는
	//Ability들을 해당 Actor의 능력으로 주게된다.
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>> PassiveToGrant);
	void InitializeDefaultAttributes(const TSubclassOf<UGameplayEffect>& AttributeEffect);
};
