// Fill out your copyright notice in the Description page of Project Settings.

#include "DevilsPlayground/GameFramework/DPHUD.h"

#include "DevilsPlayground/DPGameState.h"

void ADPHUD::BeginPlay()
{
	Super::BeginPlay();

	ADPGameState* GameState = GetWorld()->GetGameStateChecked<ADPGameState>();

	if (ensure(GameState && PlayerOwner))
	{
		GameState->CreateWidgetsForPlayer(PlayerOwner->GetLocalPlayer());
	}

}