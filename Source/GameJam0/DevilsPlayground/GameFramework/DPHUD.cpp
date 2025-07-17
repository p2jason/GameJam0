// Fill out your copyright notice in the Description page of Project Settings.

#include "DevilsPlayground/GameFramework/DPHUD.h"

#include "Widgets/CommonActivatableWidgetContainer.h"
#include "PrimaryGameLayout.h"
#include "NativeGameplayTags.h"

#include "DevilsPlayground/DPGameState.h"
#include "DevilsPlayground/DPVillager.h"
#include "DevilsPlayground/UI/DPHUDLayout.h"
#include "DevilsPlayground/UI/HUD/DPTimedLifeBar.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_GAME, "UI.Layer.Game");

void ADPHUD::OnPossessVillager(const ADPVillager* const Villager)
{
	// We should be in game and have the HUD Layout
	UDPHUDLayout* const HUDLayout = WeakHUDLayout.Get();
	if (!ensure(HUDLayout))
	{
		return;
	}
	if (UDPTimedLifeBar* const TimedLifeBar = HUDLayout->TimedLifeBar; ensure(TimedLifeBar))
	{
		if (Villager)
		{
			TimedLifeBar->UpdateLifetimeInfo(30.f, Villager->GetRemainingLife());
		}
		else
		{
			TimedLifeBar->ClearLifetimeInfo();
		}
	}
}

void ADPHUD::OnGameEnded(bool bDidWin)
{
	UDPHUDLayout* const HUDLayout = WeakHUDLayout.Get();
	if (!ensure(HUDLayout))
	{
		return;
	}
	HUDLayout->OnGameEnded(bDidWin);
}

void ADPHUD::BeginPlay()
{
	Super::BeginPlay();

	ADPGameState* GameState = GetWorld()->GetGameStateChecked<ADPGameState>();

	if (ensure(GameState && PlayerOwner))
	{
		GameState->CreateWidgetsForPlayer(PlayerOwner->GetLocalPlayer());
	}

	// Look for HUDLayout Widget
	if (UPrimaryGameLayout* const PrimaryGameLayout = UPrimaryGameLayout::GetPrimaryGameLayout(PlayerOwner))
	{
		if (const UCommonActivatableWidgetContainerBase* const LayerWidget = PrimaryGameLayout->GetLayerWidget(TAG_UI_LAYER_GAME))
		{
			if (UDPHUDLayout* HUDLayout = Cast<UDPHUDLayout>(LayerWidget->GetActiveWidget()))
			{
				WeakHUDLayout = HUDLayout;
			}
		}
	}

}
