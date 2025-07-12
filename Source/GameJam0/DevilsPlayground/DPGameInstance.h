// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonGameInstance.h"

#include "DPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM0_API UDPGameInstance : public UCommonGameInstance
{
	GENERATED_BODY()

	virtual void OnStart() override;
};
