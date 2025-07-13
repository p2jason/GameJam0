// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonActivatableWidget.h"

#include "DPActivatableWidget.generated.h"

class IWidgetCompilerLog;

struct FUIInputConfig;

UENUM(BlueprintType)
enum class EDPWidgetInputMode : uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu,
};

/**
 * An activatable widget that automatically drives the desired input config when activated
 */
UCLASS(Abstract, Blueprintable)
class UDPActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	// Begin UCommonActivatableWidget
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	// End UCommonActivatableWidget

#if WITH_EDITOR
	// Begin UUserWidget
	virtual void ValidateCompiledWidgetTree(const UWidgetTree& BlueprintWidgetTree, IWidgetCompilerLog& CompileLog) const override;
	// End UUserWidget
#endif

protected:

	// The desired input mode to use while this widget is activated, for example do you want key presses to still reach the game/player controller?
	UPROPERTY(EditDefaultsOnly, Category = Input)
	EDPWidgetInputMode InputConfig = EDPWidgetInputMode::Default;

	// The desired mouse capture behaviour when the game gets input.
	UPROPERTY(EditDefaultsOnly, Category = Input, Meta = (EditCondition = "InputConfig == EDPWidgetInputMode::Game || InputConfig == EDPWidgetInputMode::GameAndMenu"))
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;

	// The desired mouse lock behaviour.
	UPROPERTY(EditDefaultsOnly, Category = Input)
	EMouseLockMode MouseLockMode = EMouseLockMode::LockOnCapture;
};
