
#include "Inventory/InventoryComponent.h"

#include "Net/UnrealNetwork.h"

bool FPackagedInventory::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	SafeNetSerializeTArray_WithNetSerialize<100>(Ar,ItemTags,Map);
	SafeNetSerializeTArray_Default<100>(Ar,ItemQuantities);

	bOutSuccess = true;
	return true;
}

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;	
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent,CachedInventory);
}

void UInventoryComponent::AddItem(const FGameplayTag& ItemTag, int32 NumItems)
{
	AActor * Owner = GetOwner();
	if (!IsValid(Owner)) return;

	if (!Owner->HasAuthority())
	{
		ServerAddItem(ItemTag,NumItems);
		return;
	}

	if (InventoryTagMap.Contains(ItemTag))
		InventoryTagMap[ItemTag] += NumItems;
	else
		InventoryTagMap.Emplace(ItemTag,NumItems);

	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,
		FString::Printf(TEXT("Server Item Added To Inventory %s, qty : %d"),*ItemTag.ToString(),NumItems));

	PackageInventory(CachedInventory);
}

void UInventoryComponent::PackageInventory(FPackagedInventory& OutInventory)
{
	OutInventory.ItemTags.Empty();
	OutInventory.ItemQuantities.Empty();

	for (const auto & Pair : InventoryTagMap)
	{
		if (Pair.Value > 0)
		{
			OutInventory.ItemTags.Add(Pair.Key);
			OutInventory.ItemQuantities.Add(Pair.Value);
		}
	}
}

void UInventoryComponent::ReconstructInventoryMap(const FPackagedInventory& InInventory)
{
	InventoryTagMap.Empty();
	for (int32 i = 0; i < InInventory.ItemTags.Num(); ++i)
	{
		InventoryTagMap.Emplace(InInventory.ItemTags[i],InInventory.ItemQuantities[i]);

		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Blue,
			FString::Printf(TEXT("Tag Added: %s // Quantity Added: %d"),
				*InInventory.ItemTags[i].ToString(), InInventory.ItemQuantities[i]));
	}
}

void UInventoryComponent::OnRep_CachedInventory()
{
	ReconstructInventoryMap(CachedInventory);
}

void UInventoryComponent::ServerAddItem_Implementation(const FGameplayTag& ItemTag, int32 NumItems)
{
	AddItem(ItemTag,NumItems);
}
