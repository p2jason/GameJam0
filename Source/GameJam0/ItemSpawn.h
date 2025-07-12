// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawn.generated.h"

class AItemBase;

UCLASS()
class GAMEJAM0_API AItemSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly)
	TSubclassOf<AItemBase> ItemClass;

public:	

	UFUNCTION(BlueprintCallable)
	AItemBase* SpawnItem();
	
	UFUNCTION(BlueprintCallable)
	void SetItemClass(const TSubclassOf<AItemBase> NewClass) {ItemClass = NewClass; }
};
