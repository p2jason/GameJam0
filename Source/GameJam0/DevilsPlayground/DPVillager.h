// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DPVillager.generated.h"

class AItemBase;
class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDPOnInteract);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDPItemPickUp, AItemBase*, NewItem);

UCLASS()
class GAMEJAM0_API ADPVillager : public ACharacter
{
	GENERATED_BODY()

public:
	ADPVillager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;

	void SetDirectionVectors(FVector InRight, FVector InForward);

	FDPOnInteract OnInteractDelegate;

	UPROPERTY(BlueprintAssignable)
	FDPItemPickUp OnItemPickUpDelegate;
	
	float GetRemainingLife() const { return RemainingLife; }
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	AItemBase* GetHeldItem(){return HeldItem;}

	//Use this for when picking up new items, should properly swap items around
	UFUNCTION(BlueprintCallable)
	void ReplaceHeldItem(AItemBase* NewItem);

	//Use this when you want to remove the item from player without replacing it, such as for objectives maybe idk
	UFUNCTION(BlueprintCallable)
	AItemBase* RemoveHeldItem();

protected:
	UPROPERTY(EditDefaultsOnly)
	bool bCanControl = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* AbilityAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> ItemMeshComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	AItemBase* HeldItem;

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void UseAbility();

	UFUNCTION(BlueprintCallable)
	void ThrowItem();

private:
	UFUNCTION()
	void OnActorClicked(AActor* TouchedActor, FKey ButtonPressed);

	UFUNCTION()
	virtual void Move(const FInputActionValue& Value);

	UFUNCTION()
	virtual void Interact(const FInputActionValue& Value);
	
	FVector Right, Forward;

	float RemainingLife = 30.f;
};
