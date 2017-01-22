// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "MyBatteryCollectorGameMode.generated.h"

UCLASS(minimalapi)
class AMyBatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyBatteryCollectorGameMode();
	virtual void Tick(float DeltaTime) override;

protected:
	/** The rate at which the character loses power */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
	float DecayRate;
};



