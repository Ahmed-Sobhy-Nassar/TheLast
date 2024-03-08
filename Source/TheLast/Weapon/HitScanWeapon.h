// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "HitScanWeapon.generated.h"

/**
 * 
 */
UCLASS()
class THELAST_API AHitScanWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void Fire(const FVector& HitTarget) override;

protected:

	FVector TraceEndWithScatter(const FVector& TraceStart, const FVector& HitTarget);
	void WeaponTraceHit(const FVector& TraceStart, const FVector& HitTarget, FHitResult& OutHit);


	UPROPERTY(EditAnywhere, Category = "Sounds")
	class UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundCue* HitSound;

private:


	UPROPERTY(EditAnywhere)
		UParticleSystem* BeamParticles;

	UPROPERTY(EditAnywhere, Category = "Particles")
		UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Sounds")
		USoundCue* FireSound;
		
	
		/**
* Trace end with scatter
*/

		UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
		float DistanceToSphere = 800.f; // working as weapon range for now

		UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
		float SphereRadius = 75.f; // the accuracy of the weapon

		UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
		bool bUseScatter = false;

};
