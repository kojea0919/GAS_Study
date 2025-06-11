#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTags.h"
#include "InventoryComponent.generated.h"

USTRUCT()
struct FPackagedInventory
{
	GENERATED_BODY()

	virtual ~FPackagedInventory() = default;
	
	UPROPERTY()
	TArray<FGameplayTag> ItemTags;

	UPROPERTY()
	TArray<int32> ItemQuantities;

	virtual bool NetSerialize(FArchive& Ar, UPackageMap * Map, bool & bOutSuccess);
	
};

template<>
struct TStructOpsTypeTraits<FPackagedInventory> : TStructOpsTypeTraitsBase2<FPackagedInventory>
{
	enum
	{
		WithNetSerialize = true
	};
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void AddItem(const FGameplayTag & ItemTag, int32 NumItems = 1);

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TMap<FGameplayTag, int32> InventoryTagMap;

	UPROPERTY(ReplicatedUsing = OnRep_CachedInventory)
	FPackagedInventory CachedInventory;
	
	//Server : 	이 함수는 클라이언트가 호출하지만, 서버에서 실행됨
	//Reliable : 이 함수 호출은 보장됨 (패킷이 유실되면 자동 재전송됨)
	UFUNCTION(Server, Reliable) 
	void ServerAddItem(const FGameplayTag & ItemTag, int32 NumItems);

	void PackageInventory(FPackagedInventory & OutInventory);
	void ReconstructInventoryMap(const FPackagedInventory & InInventory);
	
	UFUNCTION()
	void OnRep_CachedInventory();
};
