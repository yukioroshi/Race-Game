// Copyright Epic Games, Inc. All Rights Reserved.

#include "Race_GameWheelRear.h"
#include "UObject/ConstructorHelpers.h"

URace_GameWheelRear::URace_GameWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}