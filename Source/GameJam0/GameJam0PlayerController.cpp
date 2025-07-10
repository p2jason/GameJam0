// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameJam0PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "GameJam0CameraManager.h"

AGameJam0PlayerController::AGameJam0PlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AGameJam0CameraManager::StaticClass();
}

void AGameJam0PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
