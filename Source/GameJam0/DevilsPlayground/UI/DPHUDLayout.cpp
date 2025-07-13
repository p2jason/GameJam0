// Fill out your copyright notice in the Description page of Project Settings.

#include "DevilsPlayground/UI/DPHUDLayout.h"

#include "CommonUIExtensions.h"
#include "Input/CommonUIInputTypes.h"
#include "NativeGameplayTags.h"

#include "DevilsPlayground/UI/HUD/DPTimedLifeBar.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MENU, "UI.Layer.Menu");
UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_ACTION_ESCAPE, "UI.Action.Escape");

void UDPHUDLayout::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RegisterUIActionBinding(FBindUIActionArgs(FUIActionTag::ConvertChecked(TAG_UI_ACTION_ESCAPE), false /* bShouldDisplayInActionBar */, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleEscapeAction)));
}

void UDPHUDLayout::HandleEscapeAction()
{
	if (ensure(!EscapeMenuClass.IsNull()))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), TAG_UI_LAYER_MENU, EscapeMenuClass);
	}
}
