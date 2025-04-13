
#include "RotatingHammer.h"

ARotatingHammer::ARotatingHammer()
{
	PrimaryActorTick.bCanEverTick = true;

	HammerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HammerMesh"));
	RootComponent = HammerMesh;
}

void ARotatingHammer::BeginPlay()
{
	Super::BeginPlay();
}

void ARotatingHammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator RotationStep = FRotator(RotationSpeed * DeltaTime, 0.0f, 0.0f);
	AddActorLocalRotation(RotationStep);
}
