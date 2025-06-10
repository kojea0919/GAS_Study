// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.generated.h"

//코드 중복을 피하기 위해서 제공되는 getter,setter,init함수
	#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class GAS_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

/*
 어트리뷰트 컬렉션으로, 게임 메커니즘 내에서 특정 의미를 지닌 숫자 값입니다.
 어트리뷰트는 ‘체력'과 같은 게임 리소스나, ‘기본 공격력(Base Attack Power)'
 같이 다른 게임 규칙에 영향을 줄 수 있는 레퍼런스 값을 나타낼 수 있으며,
 심지어 ‘적용된 대미지(Applied Damage)' 같이 비상태성 양도 나타낼 수 있습니다.
 어트리뷰트 세트는 하나 이상의 어트리뷰트 프로퍼티를 정의하고 관리하고 리플리케이트합니다.
 */
	
public:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	//체력
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthMax)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaMax)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxMana);
	
private:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION()
	void OnRep_HealthMax(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	void OnRep_ManaMax(const FGameplayAttributeData& OldMaxMana);
};
