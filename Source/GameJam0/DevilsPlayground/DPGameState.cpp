// Fill out your copyright notice in the Description page of Project Settings.

#include "DevilsPlayground/DPGameState.h"

#include "CommonActivatableWidget.h"
#include "CommonUIExtensions.h"
#include "Kismet/GameplayStatics.h"

#include "DevilsPlayground/GameFramework/DPHUD.h"

void ADPGameState::BeginPlay()
{
	Super::BeginPlay();
}

void ADPGameState::CreateWidgetsForPlayer(const ULocalPlayer* const LocalPlayer)
{
	for (const auto& [WidgetClass, LayerTag] /*const TPair<TSoftClassPtr<UCommonActivatableWidget>, FGameplayTag>&*/ : WidgetsToCreate)
	{
		// Initial widgets should be synchronously loaded
		UCommonUIExtensions::PushContentToLayer_ForPlayer(LocalPlayer, LayerTag, WidgetClass.LoadSynchronous());
	}
}
