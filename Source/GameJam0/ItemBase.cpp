// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AItemBase::AItemBase()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Item Mesh");
	SphereCollision = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Item Widget");
	SetRootComponent(ItemMesh);

	SphereCollision->SetupAttachment(RootComponent);
	WidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

