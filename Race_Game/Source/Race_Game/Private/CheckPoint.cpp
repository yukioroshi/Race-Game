#include "CheckPoint.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"  

ACheckPoint::ACheckPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	// Ajouter une collision box
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnCheckpointHit);
}

void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();

	// Désactiver tous les checkpoints sauf celui avec l'index 1
	if (CheckPointIndex != 1)
	{
		DeactivateCheckpoint();
	}
}

void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACheckPoint::OnCheckpointHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		// Désactiver ce checkpoint et activer le suivant
		DeactivateCheckpoint();
		for (TActorIterator<ACheckPoint> It(GetWorld()); It; ++It)
		{
			ACheckPoint* NextCheckpoint = *It;
			if (NextCheckpoint && NextCheckpoint->CheckPointIndex == CheckPointIndex + 1)
			{
				NextCheckpoint->ActivateCheckpoint();
				break;
			}
		}

		// Dessiner une ligne de debug
		DrawDebugLine(
			GetWorld(),
			GetActorLocation(),
			OtherActor->GetActorLocation(),
			FColor::Green,
			false, 2.0f, 0, 5.0f
		);
	}
}

void ACheckPoint::ActivateCheckpoint()
{
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void ACheckPoint::DeactivateCheckpoint()
{
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

