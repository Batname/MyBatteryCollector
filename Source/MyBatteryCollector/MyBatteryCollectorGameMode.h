// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "MyBatteryCollectorGameMode.generated.h"

//enum to store the current state of gameplay
UENUM(BlueprintType)
enum class EBatteryPlayState
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};

UCLASS(minimalapi)
class AMyBatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyBatteryCollectorGameMode();
	virtual void Tick(float DeltaSeconds) override;

	/** Return power needed to win */
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const { return PowerToWin; }

	virtual void BeginPlay() override;

	/** Return teh current player state */
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState GetCurrentState() const { return CurrentState; }

	/** Set a new player state */
	void SetCurrentState(EBatteryPlayState NewState);

protected:
	/** The rate at which the character loses power */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float DecayRate;

	/** The power needed to win the game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float PowerToWin;

	/** The widget class to use for our HUD screen */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	/** The instance of the HUD */
	UPROPERTY()
	class UUserWidget* CurrentWidget;

private:
	/** Keeps track ot the current state */
	EBatteryPlayState CurrentState;
};



