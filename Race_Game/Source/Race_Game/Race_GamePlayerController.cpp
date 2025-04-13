// Copyright Epic Games, Inc. All Rights Reserved.


#include "Race_GamePlayerController.h"
#include "Race_GamePawn.h"
#include "Race_GameUI.h"
#include "EnhancedInputSubsystems.h"
#include "ChaosWheeledVehicleMovementComponent.h"

void ARace_GamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// spawn the UI widget and add it to the viewport
	VehicleUI = CreateWidget<URace_GameUI>(this, VehicleUIClass);

	check(VehicleUI);

	VehicleUI->AddToViewport();
}

void ARace_GamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void ARace_GamePlayerController::Tick(float Delta)
{
	Super::Tick(Delta);

	if (IsValid(VehiclePawn) && IsValid(VehicleUI))
	{
		VehicleUI->UpdateSpeed(VehiclePawn->GetChaosVehicleMovement()->GetForwardSpeed());
		VehicleUI->UpdateGear(VehiclePawn->GetChaosVehicleMovement()->GetCurrentGear());
	}
}

void ARace_GamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// get a pointer to the controlled pawn
	VehiclePawn = CastChecked<ARace_GamePawn>(InPawn);
}
