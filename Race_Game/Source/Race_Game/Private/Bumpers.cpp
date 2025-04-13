// Fill out your copyright notice in the Description page of Project Settings.

//#include "Engine/World.h"


#include "Bumpers.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "WheeledVehiclePawn.h"  // Include this if using Chaos Vehicle System
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/MovementComponent.h"




// Sets default values
ABumpers::ABumpers()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BumperCollision"));
	RootComponent = BoxComponent;

    // Set Box Size
    BoxComponent->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));

    // Enable collision
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABumpers::OnBoxOverlap);
}

// Called when the game starts or when spawned
void ABumpers::BeginPlay()
{
	Super::BeginPlay();

    //if (GEngine)
    //    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
}

// Called every frame
void ABumpers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABumpers::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Warning, TEXT("Pushing Vehicle with Impulse!"));
        if (OtherActor->GetRootComponent())
        {
            // Get the Vehicle's Root Component (usually the mesh)
            UPrimitiveComponent* OtherActorComponent = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
            if (OtherActorComponent && OtherActorComponent->IsSimulatingPhysics())
            {
                //FVector ImpulseDirection = OtherActor->GetActorForwardVector() * 5.0f + FVector(0, 0, 1000.0f);
                //OtherActorComponent->AddImpulse(ImpulseDirection, NAME_None, true);

                FVector PushDirection;

                // Get the velocity of the vehicle
                FVector VehicleVelocity = OtherActorComponent->GetPhysicsLinearVelocity();

                if (VehicleVelocity.Size() > 10.0f) // If vehicle is moving, push it in the opposite direction
                {
                    PushDirection = -VehicleVelocity.GetSafeNormal();
                }
                else // If vehicle is stationary, push it away from the bumper
                {
                    PushDirection = SweepResult.ImpactNormal; // Push it away from the bumper
                }

                FVector ImpulseForce = OtherActor->GetActorForwardVector() * PushDirection * 4000.0f; // Adjust force as needed
                OtherActorComponent->AddImpulse(ImpulseForce, NAME_None, true);

                if (OtherActor->ActorHasTag(TEXT("VehicleBox")))
                {
                    FVector ImpulseDirection = OtherActor->GetActorForwardVector() * 5.0f + FVector(0, 0, 1000.0f);
                    OtherActorComponent->AddImpulse(ImpulseDirection, NAME_None, true);
                }
            }
        }
    }
}