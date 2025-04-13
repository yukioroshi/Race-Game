// Copyright Epic Games, Inc. All Rights Reserved.

#include "Race_GameGameMode.h"
#include "Race_GamePlayerController.h"

ARace_GameGameMode::ARace_GameGameMode()
{
	PlayerControllerClass = ARace_GamePlayerController::StaticClass();
}
