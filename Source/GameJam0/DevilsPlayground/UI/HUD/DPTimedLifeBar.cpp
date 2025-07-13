// Fill out your copyright notice in the Description page of Project Settings.

#include "DevilsPlayground/UI/HUD/DPTimedLifeBar.h"

#include "Components/ProgressBar.h"

void UDPTimedLifeBar::UpdateLifetimeInfo(const float NewMaxLifeTime, const float NewCurrentLifetime)
{
	if (ensure(NewMaxLifeTime > 0.f))
	{
		MaxLifetime = NewMaxLifeTime;
		CurrentLifetime = NewCurrentLifetime;
		bIsActive = true;
	}
}

void UDPTimedLifeBar::ClearLifetimeInfo()
{
	MaxLifetime = 0.f;
	CurrentLifetime = 0.f;
	bIsActive = false;

	check(ProgressBar);
	ProgressBar->SetPercent(0.f);
}

void UDPTimedLifeBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!bIsActive)
	{
		return;
	}

	if (CurrentLifetime > 0.f)
	{
		CurrentLifetime = FMath::Max(CurrentLifetime - InDeltaTime, 0.f);
		ProgressBar->SetPercent(CurrentLifetime / MaxLifetime);
	}
}
