// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PlayerState/RPGPlayerState.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "Attributes/RPGAttributeSet.h"

ARPGPlayerState::ARPGPlayerState()
{
	NetUpdateFrequency = 100.0f;
	MinNetUpdateFrequency = 66.0f;

	RPGAbilitySystemComp = CreateDefaultSubobject<URPGAbilitySystemComponent>("AbilitySystemComp");
	RPGAbilitySystemComp->SetIsReplicated(true);
	RPGAbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	RPGAttributes = CreateDefaultSubobject<URPGAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ARPGPlayerState::GetAbilitySystemComponent() const
{
	return RPGAbilitySystemComp;
}

URPGAbilitySystemComponent* ARPGPlayerState::GetRPGAbilitySystemComponent() const
{
	return RPGAbilitySystemComp;
}

URPGAttributeSet* ARPGPlayerState::GetRPGAttributeSet() const
{
	return RPGAttributes;
}
