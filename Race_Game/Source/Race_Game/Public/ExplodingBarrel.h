// ExplodingBarrel.h
#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "ExplodingBarrel.generated.h"

UCLASS()
class RACE_GAME_API AExplodingBarrel : public AActor
{
	GENERATED_BODY()
	
public:
	AExplodingBarrel();
		
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Explosion")
	bool bHasExploded = false;

protected:
	// Overlap trigger handler
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Explosion and destruction logic
	void Explode();
	void HandleTimerExpire();


private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BarrelMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForce;

	// Explosion configurations
	UPROPERTY(EditAnywhere, Category = "Explosion")
	float TimerDuration = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Explosion")
	float ExplosionForce = 2000.0f;

	UPROPERTY(EditAnywhere, Category = "Explosion")
	float ExplosionRadius = 500.0f;

	FTimerHandle TimerHandle;
	
};