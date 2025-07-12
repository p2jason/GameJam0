// Fill out your copyright notice in the Description page of Project Settings.


#include "DevilsPlayground/DPPlayerController.h"

#include "DPVillager.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraActor.h"

ADPPlayerController::ADPPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ADPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto Actor = GetWorld()->GetCurrentLevel()->Actors.FindByPredicate(
		[](const AActor* Actor)
		{
			return Cast<ACameraActor>(Actor) != nullptr;
		});

	if (Actor != nullptr)
	{
		WorldCamera = Cast<ACameraActor>(*Actor);
		SetViewTarget(WorldCamera);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Red, "ADD A CAMERA TO THE LEVEL! GAME WILL BREAK");
	}
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

	ADPVillager* Villager = Cast<ADPVillager>(InPawn);
	if (!IsValid(Villager)) return;
	
	Villager->SetDirectionVectors(WorldCamera->GetActorRightVector(), WorldCamera->GetActorForwardVector());
	SetViewTarget(WorldCamera);
}