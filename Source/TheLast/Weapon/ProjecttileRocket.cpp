// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjecttileRocket.h"
#include "Kismet/GameplayStatics.h"

AProjecttileRocket::AProjecttileRocket()
{
	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket Mesh"));
	RocketMesh->SetupAttachment(RootComponent);
	RocketMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AProjecttileRocket::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APawn* FiringPawn = GetInstigator();
	if (FiringPawn)
	{
		AController* FiringController = FiringPawn->GetController();
		if (FiringController)
		{
			UGameplayStatics::ApplyRadialDamageWithFalloff(
				this, // World Context Object
				Damage,     // Base Damage
				MinimumDamage, // 
				GetActorLocation(), //Origin
				DamageInnerRadius,
				DamageOuterRadius,
				DamageFalloff, // 
				UDamageType::StaticClass(), // Damage Type
				TArray<AActor*>(), // IgnoreActors
				this,    // Damage Causer
				FiringController // InstigatorController

			);
		}
	}
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}
