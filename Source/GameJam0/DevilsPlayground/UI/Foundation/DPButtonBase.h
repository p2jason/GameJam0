// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonButtonBase.h"

#include "DPButtonBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class UDPButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetButtonText(const FText& InText);

protected:

	// Begin UUserWidget
	virtual void NativePreConstruct() override;
	// End UUserWidget

	// Begin UCommonButtonBase
	virtual void UpdateInputActionWidget() override;
	// End UCommonButtonBase

	void RefreshButtonText();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateButtonText(const FText& InText);

private:

	UPROPERTY(EditAnywhere, Category = Button, Meta = (InlineEditConditionToggle))
	bool bOverrideButtonText = true;

	UPROPERTY(EditAnywhere, Category = Button, Meta = (EditCondition = bOverrideButtonText))
	FText ButtonText;
};
