// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags.h"
#include "CharacterClassInfo.generated.h"

class UGameplayEffect;
class UGameplayAbility;

//FCharacterClassDefaultInfo구조체
USTRUCT()
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultAttributes;
	//UGameplayEffect는 Ability가 자신을 포함한 다른 객체의 Attribute및 GameplayTag를
	//변경하기 위한 수단이다.(https://kkadalg.tistory.com/37)

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;
	//UGameplayAbility 게임에서 어떠한 능력, 행동 등 다양한 것을 어빌리티로
	//정하고 그걸 GameplayAbility로 구현할 수 있다.
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> StartingPassives;
};

/**
 * 
 */
UCLASS()
class GAS_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	//FGameplayTag가 Key
	//FCharacterClassDefaultInfo가 Value인 ClassDefaultInfoMap이 존재
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FCharacterClassDefaultInfo> ClassDefaultInfoMap;
};
