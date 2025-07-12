// Fill out your copyright notice in the Description page of Project Settings.

#include "DevilsPlayground/DPVillager.h"

#include "DPPlayerController.h"
#include "EnhancedInputComponent.h"
#include "ItemBase.h"

ADPVillager::ADPVillager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMeshComponent->SetupAttachment(RootComponent);
	
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

void ADPVillager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsControlled()) return;

	RemainingLife -= DeltaSeconds;

	if (RemainingLife <= 0.f)
	{
		Destroy();
	}
}

void ADPVillager::SetDirectionVectors(FVector InRight, FVector InForward)
{
	Right = InRight;
	Forward = InForward;
}

void ADPVillager::ReplaceHeldItem(AItemBase* NewItem)
{
	if(HeldItem)
	{
		//ThrowItem();
		HeldItem->SetActorHiddenInGame(false);
		HeldItem->SetActorTransform(NewItem->GetTransform());
	}
	NewItem->SetActorHiddenInGame(true);
	
	HeldItem = NewItem;

	OnItemPickUpDelegate.Broadcast(HeldItem);
	
	ItemMeshComponent->SetStaticMesh(HeldItem->ItemMesh->GetStaticMesh());
}

AItemBase* ADPVillager::RemoveHeldItem()
{
	AItemBase* Out = HeldItem;
	Out->SetActorHiddenInGame(false);
	ItemMeshComponent->SetStaticMesh(nullptr);
	HeldItem = nullptr;
	OnItemPickUpDelegate.Broadcast(HeldItem);
	return Out;
}

void ADPVillager::PossessedBy(AController* NewController)
{
	if (!IsValid(Cast<ADPPlayerController>(NewController))) return;

	StaticMesh->SetRenderCustomDepth(true);
}

void ADPVillager::UnPossessed()
{
	StaticMesh->SetRenderCustomDepth(false);
}

void ADPVillager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADPVillager::Move);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ADPVillager::Interact);
		EnhancedInputComponent->BindAction(AbilityAction, ETriggerEvent::Started, this, &ADPVillager::UseAbility);
	}
}

void ADPVillager::ThrowItem()
{
	HeldItem->SetActorTransform(GetActorTransform());
	HeldItem->SetActorLocation( HeldItem->GetActorLocation() + HeldItem->GetActorForwardVector() * 1000.0f);
	HeldItem->SetActorHiddenInGame(false);
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

void ADPVillager::Interact(const FInputActionValue& Value)
{
	OnInteractDelegate.Broadcast();
}
