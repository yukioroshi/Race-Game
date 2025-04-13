#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPoint.generated.h"

UCLASS()
class ACheckPoint : public AActor
{
	GENERATED_BODY()

public:
	ACheckPoint();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Identifiant du checkpoint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
	int32 CheckPointIndex;

	// Détection de collision avec le joueur
	UFUNCTION()
	void OnCheckpointHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	// Activer le checkpoint
	void ActivateCheckpoint();

	// Désactiver le checkpoint
	void DeactivateCheckpoint();

private:
	// Déclaration de la collision box
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* CollisionBox;
};

