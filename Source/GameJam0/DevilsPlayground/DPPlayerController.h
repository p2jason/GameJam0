// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "DPPlayerController.generated.h"

class ADPVillager;
class UInputMappingContext;
class UInputAction;
class ACameraActor;

struct FInputActionInstance;

class ADPPawnBase;
/**
 * 
 */
UCLASS()
class GAMEJAM0_API ADPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADPPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input", meta = (AllowPrivateAccess = "true"))
	TArray<UInputMappingContext*> DefaultMappingContexts;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* RotateAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	float RotateSpeed = 90.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ZoomAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	float ZoomSpeed = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	float PanSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	float PanEdgeRange = 10.f;

private:
	UPROPERTY()
	TObjectPtr<ACameraActor> WorldCamera = nullptr;

	UFUNCTION()
	void RotateCamera(const FInputActionValue& Value);

	UFUNCTION()
	void ZoomCamera(const FInputActionValue& Value);

	UFUNCTION()
	void PanCamera(float DeltaSeconds);
};
