// Fill out your copyright notice in the Description page of Project Settings.

#include "DevilsPlayground/UI/Foundation/DPButtonBase.h"

#include "CommonActionWidget.h"

void UDPButtonBase::SetButtonText(const FText& InText)
{
	bOverrideButtonText = InText.IsEmpty();
	ButtonText = InText;
	RefreshButtonText();
}

void UDPButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	RefreshButtonText();
}

void UDPButtonBase::UpdateInputActionWidget()
{
	Super::UpdateInputActionWidget();

	RefreshButtonText();
}

void UDPButtonBase::RefreshButtonText()
{
	if (bOverrideButtonText || ButtonText.IsEmpty())
	{
		if (InputActionWidget)
		{
			const FText ActionDisplayText = InputActionWidget->GetDisplayText();
			if (!ActionDisplayText.IsEmpty())
			{
				UpdateButtonText(ActionDisplayText);
				return;
			}
		}
	}

	UpdateButtonText(ButtonText);
}
