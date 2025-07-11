// Fill out your copyright notice in the Description page of Project Settings.


#include "DevilsPlayground/DPPawnBase.h"

// Sets default values
ADPPawnBase::ADPPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADPPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADPPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADPPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

