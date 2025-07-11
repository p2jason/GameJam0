// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DPGameState.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM0_API ADPGameState : public AGameStateBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};
