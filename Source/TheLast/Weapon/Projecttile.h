// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projecttile.generated.h"

UCLASS()
class THELAST_API AProjecttile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjecttile();
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

protected:

	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UPROPERTY(EditAnywhere)
		float Damage = 20.f;

private:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Trace;
	class UParticleSystemComponent* TraceComponent;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactParticles;
	UPROPERTY(EditAnywhere)
	class USoundCue* ImpactSound;


public:	


};
