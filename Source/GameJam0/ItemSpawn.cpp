// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawn.h"

#include "ItemBase.h"

// Sets default values
AItemSpawn::AItemSpawn()
{
}

// Called when the game starts or when spawned
void AItemSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemSpawn::SpawnItem()
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AItemBase>(ItemClass, GetActorLocation(), GetActorRotation(), params);
}
