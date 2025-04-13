// Fill out your copyright notice in the Description page of Project Settings.

#include "BoostPickup.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/MovementComponent.h"

ABoostPickup::ABoostPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	BoostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoostMesh"));
	BoostMesh->SetupAttachment(RootComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABoostPickup::OnOverlapBegin);
}

void ABoostPickup::BeginPlay()
{
	Super::BeginPlay();
}

void ABoostPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoostPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		// Vérifier si l'acteur est valide et s'il a un composant racine
		if (OtherActor->GetRootComponent())
		{
			// Appliquer l'impulsion vers l'avant
			UPrimitiveComponent* OtherActorComponent = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
			if (OtherActorComponent && OtherActorComponent->IsSimulatingPhysics())
			{
				FVector ForwardImpulse = OtherActor->GetActorForwardVector() * BoostStrength;
				OtherActorComponent->AddImpulse(ForwardImpulse, NAME_None, true);

				// Déclencher le timer pour appliquer l'impulsion en arrière après 2 secondes
				FTimerDelegate TimerDel;
				TimerDel.BindUObject(this, &ABoostPickup::ResetBoostStrength, OtherActor);
				GetWorldTimerManager().SetTimer(BoostResetTimerHandle, TimerDel, 2.0f, false);
			}
		}

		// Cacher le boost
		BoostMesh->SetVisibility(false);
		BoostMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Timer pour respawn après 5 secondes
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ABoostPickup::RespawnBoost, 5.0f, false);
	}
}

void ABoostPickup::ResetBoostStrength(AActor* AffectedActor)
{
	if (AffectedActor && AffectedActor->GetRootComponent())
	{
		UPrimitiveComponent* AffectedComponent = Cast<UPrimitiveComponent>(AffectedActor->GetRootComponent());
		if (AffectedComponent && AffectedComponent->IsSimulatingPhysics())
		{
			FVector BackwardImpulse = -AffectedActor->GetActorForwardVector() * BoostStrength;
			AffectedComponent->AddImpulse(BackwardImpulse, NAME_None, true);
		}
	}
}

void ABoostPickup::RespawnBoost()
{
	BoostMesh->SetVisibility(true);
	BoostMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
