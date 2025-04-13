// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Race_GamePlayerController.generated.h"

class UInputMappingContext;
class ARace_GamePawn;
class URace_GameUI;

/**
 *  Vehicle Player Controller class
 *  Handles input mapping and user interface
 */
UCLASS(abstract)
class RACE_GAME_API ARace_GamePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	/** Pointer to the controlled vehicle pawn */
	TObjectPtr<ARace_GamePawn> VehiclePawn;

	/** Type of the UI to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<URace_GameUI> VehicleUIClass;

	/** Pointer to the UI widget */
	TObjectPtr<URace_GameUI> VehicleUI;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:

	virtual void Tick(float Delta) override;

	// End Actor interface

	// Begin PlayerController interface
protected:

	virtual void OnPossess(APawn* InPawn) override;

	// End PlayerController interface
};
