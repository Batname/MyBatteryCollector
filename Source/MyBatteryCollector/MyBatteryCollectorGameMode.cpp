// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MyBatteryCollector.h"
#include "MyBatteryCollectorGameMode.h"
#include "MyBatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

AMyBatteryCollectorGameMode::AMyBatteryCollectorGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	} 

	// base decay rate
	DecayRate = 0.01f;
}

void AMyBatteryCollectorGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Check that we are using battery collection character
	AMyBatteryCollectorCharacter* MyCharacter = Cast<AMyBatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		// if power is grather then needed set to win
		if (MyCharacter->GetCurrentPower() > PowerToWin)
		{
			SetCurrentState(EBatteryPlayState::EWon);
		}
		else if (MyCharacter->GetCurrentPower() > 0)
		{
			// Decrease power
			MyCharacter->UpdatePower(-DeltaSeconds * DecayRate * (MyCharacter->GetInitialPower()));
		}
		else
		{
			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}
}

void AMyBatteryCollectorGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentState(EBatteryPlayState::EPlaying);

	// set the game score to beat
	AMyBatteryCollectorCharacter* MyCharacter = Cast<AMyBatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = (MyCharacter->GetInitialPower()) * 1.25f;
	}

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

EBatteryPlayState AMyBatteryCollectorGameMode::GetCurrentState() const
{
	return CurrentState;
}

void AMyBatteryCollectorGameMode::SetCurrentState(EBatteryPlayState NewState)
{
	CurrentState = NewState;
}
