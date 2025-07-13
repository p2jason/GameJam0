// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DevilsPlayground/UI/DPActivatableWidget.h"

#include "DPHUDLayout.generated.h"

class UDPTimedLifeBar;

/**
 * UDPHUDLayout
 * 
 * Widget to lay out the player's HUD
 */
UCLASS(Abstract, BlueprintType, Blueprintable, Meta = (DisplayName = "DP HUD Layout", Category = "DP|HUD"))
class UDPHUDLayout : public UDPActivatableWidget
{
	GENERATED_BODY()

public:

	// Begin UUserWidget
	virtual void NativeOnInitialized() override;
	// End UUserWidget

public:

	// Very hacky way of easy access to potential widgets in the layout
	UPROPERTY(Meta = (BindWidgetOptional))
	TObjectPtr<UDPTimedLifeBar> TimedLifeBar;

protected:

	void HandleEscapeAction();

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UCommonActivatableWidget> EscapeMenuClass;
	
};
