// Fill out your copyright notice in the Description page of Project Settings.


#include "DevilsPlayground/DPPlayerController.h"

#include "DPVillager.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"

#include "DevilsPlayground/GameFramework/DPHUD.h"

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

void ADPPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PanCamera(DeltaSeconds);
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

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ADPPlayerController::RotateCamera);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ADPPlayerController::ZoomCamera);
	}
}

void ADPPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ADPVillager* Villager = Cast<ADPVillager>(InPawn);
	if (!IsValid(Villager)) return;
	
	FVector Right = WorldCamera->GetActorRightVector();
	Right.Z = 0;
	
	FVector Forward = WorldCamera->GetActorForwardVector();
	Forward.Z = 0;
		
	Villager->SetDirectionVectors(Right, Forward);
	
	SetViewTarget(WorldCamera);

	// Update HUD
	if (ADPHUD* const HUD = Cast<ADPHUD>(MyHUD))
	{
		HUD->OnPossessVillager(Villager);
	}
}

void ADPPlayerController::RotateCamera(const FInputActionValue& Value)
{
	float RotationDelta = Value.Get<float>() * RotateSpeed * GetWorld()->DeltaTimeSeconds;

	float Radians = FMath::DegreesToRadians(RotationDelta);
	float Sin = FMath::Sin(Radians);
	float Cos = FMath::Cos(Radians);
	
	FVector Location = WorldCamera->GetActorLocation();
	FVector Pivot = Location + WorldCamera->GetActorForwardVector() * RotateRadius;
	FVector Start = Location - Pivot;

	float NewX = Start.X * Cos - Start.Y * Sin + Pivot.X;
	float NewY = Start.X * Sin + Start.Y * Cos + Pivot.Y;
	WorldCamera->SetActorLocation(FVector(NewX, NewY, Location.Z));

	FVector Direction = Pivot - WorldCamera->GetActorLocation();
	FRotator NewRotation = Direction.Rotation();
	WorldCamera->SetActorRotation(NewRotation);
	
	if (ADPVillager* Villager = Cast<ADPVillager>(GetPawn()); IsValid(Villager))
	{
		FVector Right = WorldCamera->GetActorRightVector();
		Right.Z = 0;
	
		FVector Forward = WorldCamera->GetActorForwardVector();
		Forward.Z = 0;
		
		Villager->SetDirectionVectors(Right, Forward);
	}
}

void ADPPlayerController::ZoomCamera(const FInputActionValue& Value)
{
	UCameraComponent* CameraComp = WorldCamera->GetCameraComponent();
	float FoV = CameraComp->FieldOfView + Value.Get<float>() * ZoomSpeed;
	CameraComp->SetFieldOfView(FMath::Clamp(FoV, 15.f, 120.f));
}

void ADPPlayerController::PanCamera(float DeltaSeconds)
{
	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);

	int32 Width, Height;
	GetViewportSize(Width, Height);

	FVector Right = WorldCamera->GetActorRightVector();
	Right.Z = 0;
	Right *= PanSpeed * DeltaSeconds;
	
	FVector Forward = WorldCamera->GetActorForwardVector();
	Forward.Z = 0;
	Forward *= PanSpeed * DeltaSeconds;

	float DistanceFromSide = Width * PanEdgeRange;
	float DistanceFromTop = Height * PanEdgeRange;
	
	if (MouseX <= DistanceFromSide) WorldCamera->AddActorWorldOffset(-Right);
	else if (MouseX >= Width - DistanceFromSide) WorldCamera->AddActorWorldOffset(Right);

	if (MouseY <= DistanceFromTop) WorldCamera->AddActorWorldOffset(Forward);
	else if (MouseY >= Height - DistanceFromTop) WorldCamera->AddActorWorldOffset(-Forward);
}
