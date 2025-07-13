// Fill out your copyright notice in the Description page of Project Settings.


#include "DevilsPlayground/DPInteractableComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogInteraction, Verbose, All);

// Sets default values for this component's properties
UDPInteractableComponent::UDPInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Create and attach a sphere component
	InteractionArea = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionArea"));
	InteractionArea->SetupAttachment(this);
}


// Called when the game starts
void UDPInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	InteractionArea->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnInteractionAreaBeginOverlap);
	InteractionArea->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInteractionAreaEndOverlap);
}


// Called every frame
void UDPInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UDPInteractableComponent::OnInteractionAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	UE_LOG(LogInteraction, Verbose, TEXT("Entered Interaction Area"));

	InteractingActor = OtherActor;

	if (bInteractOnOverlap) 
	{
		BeginInteraction();
	}
	else 
	{
		ADPVillager* Villager = Cast<ADPVillager>(OtherActor);

		if (Villager)
		{
			Villager->OnInteractDelegate.AddDynamic(this, &UDPInteractableComponent::BeginInteraction);
		}
	}
}

void UDPInteractableComponent::OnInteractionAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogInteraction, Verbose, TEXT("Left Interaction Area"));

	if (bInteractOnOverlap)
	{
		EndInteraction();
	}
	else 
	{
		ADPVillager* Villager = Cast<ADPVillager>(OtherActor);

		if (Villager)
		{
			Villager->OnInteractDelegate.RemoveDynamic(this, &UDPInteractableComponent::EndInteraction);
		}
	}

	InteractingActor = nullptr;
}

void UDPInteractableComponent::BeginInteraction() 
{	
	OnInteractionBegin.Broadcast();
}

void UDPInteractableComponent::CancelInteraction()
{
	OnInteractionCancelled.Broadcast();

	InteractingActor = nullptr;
}

void UDPInteractableComponent::EndInteraction()
{
	OnInteractionEnd.Broadcast();

	InteractingActor = nullptr;
}


