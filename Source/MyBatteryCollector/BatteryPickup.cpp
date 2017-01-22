// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBatteryCollector.h"
#include "BatteryPickup.h"

/* set default values */
ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);

	// the base powel level of the battery
	BatteryPower = 150.0f;
}

void ABatteryPickup::WasCollected_Implementation()
{
	// Use the base pickup behavior
	Super::WasCollected_Implementation();

	// Destroy the battery
	Destroy();
}