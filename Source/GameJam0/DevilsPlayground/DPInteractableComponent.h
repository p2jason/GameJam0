// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Delegates/DelegateCombinations.h"
#include "DPVillager.h"
#include "DPInteractableComponent.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAM0_API UDPInteractableComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDPInteractableComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Delegate events
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionEvent OnInteractionBegin;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionEvent OnInteractionCancelled;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionEvent OnInteractionEnd;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	USphereComponent* InteractionArea;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	bool bInteractOnOverlap = false;

	AActor* InteractingActor;

	UFUNCTION()
	void OnInteractionAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnInteractionAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void BeginInteraction();

	UFUNCTION()
	void CancelInteraction();

	UFUNCTION()
	void EndInteraction();
};
