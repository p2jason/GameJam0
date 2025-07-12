// Fill out your copyright notice in the Description page of Project Settings.


#include "DevilsPlayground/DPPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/CameraActor.h"

ADPPlayerController::ADPPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ADPPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ADPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}

void ADPPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}