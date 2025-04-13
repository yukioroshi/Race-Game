// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Race_GamePawn.h"
#include "Race_GameSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class RACE_GAME_API ARace_GameSportsCar : public ARace_GamePawn
{
	GENERATED_BODY()
	
public:

	ARace_GameSportsCar();
};
