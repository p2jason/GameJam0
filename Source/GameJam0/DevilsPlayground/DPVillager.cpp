// Fill out your copyright notice in the Description page of Project Settings.


#include "DevilsPlayground/DPVillager.h"

#include "DPPlayerController.h"
#include "EnhancedInputComponent.h"

ADPVillager::ADPVillager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	
 	PrimaryActorTick.bCanEverTick = true;
}

void ADPVillager::BeginPlay()
{
	Super::BeginPlay();

	OnClicked.AddDynamic(this, &ADPVillager::OnActorClicked);
}

void ADPVillager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnClicked.RemoveAll(this);
	
	Super::EndPlay(EndPlayReason);
}

void ADPVillager::SetDirectionVectors(FVector InRight, FVector InForward)
{
	Right = InRight;
	Forward = InForward;
}

void ADPVillager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADPVillager::Move);
	}
}

void ADPVillager::OnActorClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	if (!bCanControl) return;

	const UWorld* World = GetWorld();
	if (!IsValid(World)) return;
	
	ADPPlayerController* PlayerController = Cast<ADPPlayerController>(World->GetFirstPlayerController());
	if (!IsValid(PlayerController)) return;

	PlayerController->Possess(this);
}

void ADPVillager::Move(const FInputActionValue& Value)
{
	if (!GetController()) return;
	
	FVector2D MovementVector = Value.Get<FVector2D>();

	AddMovementInput(Right, MovementVector.X);
	AddMovementInput(Forward, MovementVector.Y);
}
