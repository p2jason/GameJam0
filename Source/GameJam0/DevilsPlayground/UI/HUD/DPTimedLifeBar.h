// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DPTimedLifeBar.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class UDPTimedLifeBar : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateLifetimeInfo(const float NewMaxLifeTime, const float NewCurrentLifetime);

	void ClearLifetimeInfo();

protected:

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;

	// Begin UUserWidget
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	// End UUserWidget

	float MaxLifetime = 0.f;
	float CurrentLifetime = 0.f;

	// Should Lifetime Update
	bool bIsActive = false;
	
};
