// ExplodingBarrel.cpp
#include "ExplodingBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "TimerManager.h"

AExplodingBarrel::AExplodingBarrel()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set up collision box
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AExplodingBarrel::OnOverlapBegin);

	// Set up barrel mesh
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	BarrelMesh->SetupAttachment(RootComponent);

	// Set up radial force component
	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForce->SetupAttachment(RootComponent);
	RadialForce->Radius = ExplosionRadius;
	RadialForce->ImpulseStrength = ExplosionForce;
	RadialForce->bImpulseVelChange = true;
	RadialForce->bIgnoreOwningActor = true;
}

void AExplodingBarrel::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bHasExploded)
		Explode();
}

void AExplodingBarrel::Explode()
{
	bHasExploded = true;

	// Apply radial force and start destruction timer
	RadialForce->FireImpulse();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AExplodingBarrel::HandleTimerExpire, TimerDuration, false);

	UE_LOG(LogTemp, Warning, TEXT("Explosion initiated. Barrel will disappear after delay of %f seconds."), TimerDuration);
}

void AExplodingBarrel::HandleTimerExpire()
{
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Barrel destroyed after delay."));
}