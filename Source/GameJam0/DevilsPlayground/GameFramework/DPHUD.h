// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"

#include "DPHUD.generated.h"

/**
 * 
 */
UCLASS()
class ADPHUD : public AHUD
{
	GENERATED_BODY()

protected:

	// Begin AActor
	virtual void BeginPlay() override;
	// End AActor
	
};
