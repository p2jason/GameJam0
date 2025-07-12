// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

#include "ItemSpawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItemManager::AItemManager()
{
}

void AItemManager::PopulateWorld()
{
	for (AActor* Spawn : ItemSpawns)
	{
		Cast<AItemSpawn>(Spawn)->SpawnItem();
	}
}

// Called when the game starts or when spawned
void AItemManager::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawn::StaticClass(), ItemSpawns);

	PopulateWorld();
}

