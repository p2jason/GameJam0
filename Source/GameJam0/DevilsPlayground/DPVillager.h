// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DPVillager.generated.h"

class UInputAction;

UCLASS()
class GAMEJAM0_API ADPVillager : public ACharacter
{
	GENERATED_BODY()

public:
	ADPVillager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SetDirectionVectors(FVector InRight, FVector InForward);
	
protected:
	UPROPERTY(EditDefaultsOnly)
	bool bCanControl = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	UFUNCTION()
	void OnActorClicked(AActor* TouchedActor, FKey ButtonPressed);

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void Move(const FInputActionValue& Value);

	FVector Right, Forward;
};
