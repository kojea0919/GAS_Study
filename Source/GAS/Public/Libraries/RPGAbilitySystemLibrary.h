// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGAbilitySystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API URPGAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//UBlueprintFunctionLibrary는 프로젝트를 개발하는 동안,
	//프로젝트의 여러 부분에 필요한 몇 가지 함수를 C++와 Blueprints에서 모두 만들어야 한다.
	//이런 경우, C++에서 Blueprint 함수 라이브러리를 만들어서 이런 함수를 한 곳에 모을 수 있다.
public:
	UFUNCTION(BlueprintPure)
	static UCharacterClassInfo * GetCharacterClassDefaultInfo(const UObject* WorldContextObject);
};
