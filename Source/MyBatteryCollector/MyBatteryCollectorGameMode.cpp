// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MyBatteryCollector.h"
#include "MyBatteryCollectorGameMode.h"
#include "MyBatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"

AMyBatteryCollectorGameMode::AMyBatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// base decay rate
	DecayRate = 0.01f;
}

void AMyBatteryCollectorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check that we are using battery collection character
	AMyBatteryCollectorCharacter* MyCharacter = Cast<AMyBatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		if (MyCharacter->GetCurrentPower() > 0)
		{
			// Decrease power
			MyCharacter->UpdatePower(-DeltaTime * DecayRate * (MyCharacter->GetInitialPower()));
		}
	}
}
