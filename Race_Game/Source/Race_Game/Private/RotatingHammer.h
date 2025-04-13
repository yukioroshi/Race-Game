// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingHammer.generated.h"

UCLASS()
class ARotatingHammer : public AActor
{
	GENERATED_BODY()
	
public:
	ARotatingHammer();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HammerMesh;

	UPROPERTY(EditAnywhere, Category="Rotation")
	float RotationSpeed = 90.0f;
};
