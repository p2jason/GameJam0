// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
	
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;
};
