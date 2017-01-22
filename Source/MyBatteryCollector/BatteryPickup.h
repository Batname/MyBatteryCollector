// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class MYBATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public:
	/* set default values */
	ABatteryPickup();

	/** ovveride WasCollected Function */
	void WasCollected_Implementation() override;

	/** public way to access the bettery power level */
	FORCEINLINE float GetPower() const { return BatteryPower; }
	
protected:
	/** set the amout of power */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float BatteryPower;
};
