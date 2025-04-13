// Copyright Epic Games, Inc. All Rights Reserved.

#include "Race_GameWheelFront.h"
#include "UObject/ConstructorHelpers.h"

URace_GameWheelFront::URace_GameWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}