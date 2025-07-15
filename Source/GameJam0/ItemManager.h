// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "GameFramework/Actor.h"
#include "ItemManager.generated.h"

class AItemBase;
class AItemSpawn;

UCLASS()
class GAMEJAM0_API AItemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemManager();

	void PopulateWorld();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TArray<AActor*> ItemSpawns;

	UPROPERTY(BlueprintReadWrite)
	TArray<AItemBase*> SpawnedItems;
public:
	UFUNCTION(BlueprintCallable)
	AItemBase* FindItemByType(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	TArray<AItemBase*> GetSpawnedItems(){return SpawnedItems;}
};
