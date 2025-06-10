// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/RPGAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

void URPGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	//URPGAttributeSet : 복제를 설정할 클래스
	//Heatlh : 복제할 멤버 변수
	//COND_None : 항상 복제
	//REPNOTIFY_Always : 값이 바뀌지 않았더라도 항상 호출
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
}

void URPGAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	//PostGameplayEffectExecute함수는
	//GameplayEffect가 속성에 영향을 준 직후에 자동으로 호출됩니다.
	//여기서 속성값을 정리하거나, 조건 검사, 부가 작업 등을 할 수 있습니다.
	Super::PostGameplayEffectExecute(Data);

	//GameplayEffect가 바꾼게 Health인 경우
	//----------------------------------------------------------
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.f,GetMaxHealth()));
	}
	//----------------------------------------------------------

	//GameplayEffect가 바꾼게 Mana인 경우
	//----------------------------------------------------------
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(),0.f,GetMaxMana()));
	}
	//----------------------------------------------------------
}

void URPGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet,Health,OldHealth);
	//GAMEPLAYATTRIBUTE_REPNOTIFY
	// Health 값이 복제되었을 때: OnRep_Health()가 클라이언트에서 호출됨.
	// GAMEPLAYATTRIBUTE_REPNOTIFY(...)를 통해 AttributeValueChanged(...) 호출.
	// GAS 내부에서: Attribute 변화 이벤트 브로드캐스트
	// Attribute 기반 이펙트, UI 업데이트 등 트리거 가능
	// 즉, GAS가 자동으로 Health 변경을 인지하고 반응하도록 연결하는 핵심 연결 고리입니다.
}

void URPGAttributeSet::OnRep_HealthMax(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet,MaxHealth,OldMaxHealth);
}

void URPGAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet,Mana,OldMana);
}

void URPGAttributeSet::OnRep_ManaMax(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet,MaxMana,OldMaxMana);
}

