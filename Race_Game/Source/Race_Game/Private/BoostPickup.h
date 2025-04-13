// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoostPickup.generated.h"

UCLASS()
class ABoostPickup : public AActor
{
	GENERATED_BODY()

public:
	ABoostPickup();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* BoostMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	float BoostStrength = 2000.0f;

	UPROPERTY(EditAnywhere, Category = "Components")
	float InvertBoostStrength = -2000.0f;


	FTimerHandle RespawnTimerHandle;
	FTimerHandle BoostResetTimerHandle;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ResetBoostStrength(AActor* AffectedActor);

	void RespawnBoost();
};
