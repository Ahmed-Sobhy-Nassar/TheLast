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


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinimumDamage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Range;
protected:

	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



	UPROPERTY(EditAnywhere)
		class UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere)
		class USoundCue* ImpactSound;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionBox;


	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileMovementComponent;

		



private:


	UPROPERTY(EditAnywhere)
		 UParticleSystem* Trace;

	class UParticleSystemComponent* TraceComponent;


public:	
 
};
