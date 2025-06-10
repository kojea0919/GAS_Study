// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "RPGGameMode.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class GAS_API ARPGGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UCharacterClassInfo* GetCharacterClassDefaultInfo() const;

private:
	//FCharacterClassDefaultInfo Map으로 관리하는 UCharacterClassInfo를 가리키는 포인터를 가지고 있음
	//어떤 캐릭터의 정해진 Ability들을 FCharacterClassDefaultInfo에 저장하고
	//그 정보를 GameplayTag로 UCharacterClassInfo에서 Map으로 관리하고 그것에 대한
	//포인터를 GameMode가 가리키고 있는 상태 GameMode는 모든 것을 알고 있게 함
	UPROPERTY(EditDefaultsOnly, Category = "Custom Values|Class Defaults")
	TObjectPtr<UCharacterClassInfo> ClassDefaults;
};
