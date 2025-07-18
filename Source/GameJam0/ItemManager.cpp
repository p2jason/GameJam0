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
	for (TTuple<TSubclassOf<AItemBase>, int>  Spawn : ItemSpawnMap)
	{
		for (int i =0; i< Spawn.Value; i++)
		{
			const int index = FMath::RandRange(0, ItemSpawns.Num()-1);
			const AActor* Spawner = ItemSpawns[index];
			ItemSpawns.RemoveAt(index);
			
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnedItems.Add(GetWorld()->SpawnActor<AItemBase>(Spawn.Key, Spawner->GetActorLocation(), Spawner->GetActorRotation(), Params));

			if(ItemSpawns.Num()==0)
				return;
		}
	}
	//OLD
	// for (AActor* Spawner : ItemSpawns)
	// {
	// 	if(AItemBase* SpawnedItem = Cast<AItemSpawn>(Spawner)->SpawnItem(); SpawnedItem->IsValidLowLevel())
	// 		SpawnedItems.Add(SpawnedItem);
	// }
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

