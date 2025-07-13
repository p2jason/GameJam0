// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"

#include "DPHUD.generated.h"

class ADPVillager;
class UDPHUDLayout;

/**
 * 
 */
UCLASS()
class ADPHUD : public AHUD
{
	GENERATED_BODY()

public:

	void OnPossessVillager(const ADPVillager* const Villager);

protected:

	// Begin AActor
	virtual void BeginPlay() override;
	// End AActor

	// Most of the time the HUD will have a HUDLayout, might as well store a pointer to it
	TWeakObjectPtr<UDPHUDLayout> WeakHUDLayout;
	
};
