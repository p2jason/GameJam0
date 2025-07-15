// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

#include "ItemBase.h"
#include "ItemSpawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItemManager::AItemManager()
{
}

void AItemManager::PopulateWorld()
{
	for (AActor* Spawner : ItemSpawns)
	{
		if(AItemBase* SpawnedItem = Cast<AItemSpawn>(Spawner)->SpawnItem(); SpawnedItem->IsValidLowLevel())
			SpawnedItems.Add(SpawnedItem);
	}
}

// Called when the game starts or when spawned
void AItemManager::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawn::StaticClass(), ItemSpawns);

	PopulateWorld();
}

AItemBase* AItemManager::FindItemByType(FGameplayTag Tag)
{
	return *SpawnedItems.FindByPredicate([&](AItemBase* N)
	{
		return N->ItemTag == Tag;
	});
}

