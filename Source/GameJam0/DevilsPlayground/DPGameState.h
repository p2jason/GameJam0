// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"

#include "NativeGameplayTags.h"

#include "DPGameState.generated.h"

class UCommonActivatableWidget;
class ULocalPlayer;


/**
 * 
 */
UCLASS()
class GAMEJAM0_API ADPGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	void CreateWidgetsForPlayer(const ULocalPlayer* const LocalPlayer);

protected:

	// Begin AActor
	virtual void BeginPlay() override;
	// End AActor

protected:

	UPROPERTY(EditDefaultsOnly, Category = UI, Meta = (Categories = "UI.Layer"))
	TMap<TSoftClassPtr<UCommonActivatableWidget>, FGameplayTag> WidgetsToCreate;
};
