// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projecttile.h"
#include "ProjecttileRocket.generated.h"

/**
 * 
 */
UCLASS()
class THELAST_API AProjecttileRocket : public AProjecttile
{
	GENERATED_BODY()
public:
	AProjecttileRocket();
	virtual void Destroyed() override;

protected:
	
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void BeginPlay() override;
	void DestroyTimerFinished();

	UPROPERTY(EditAnywhere)
		float DamageInnerRadius = 200.f;
	UPROPERTY(EditAnywhere)
		float DamageOuterRadius = 500.f;
	UPROPERTY(EditAnywhere)
		float DamageFalloff = 1.f;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* TrailSystem;
	
	UPROPERTY()
		class UNiagaraComponent* TrailSystemComponent;

	UPROPERTY(EditAnywhere)
		USoundCue* ProjectileLoop;

	UPROPERTY()
		UAudioComponent* ProjectileLoopComponent;

	UPROPERTY(EditAnywhere)
		USoundAttenuation* LoopingSoundAttenuation;

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* RocketMesh;

	FTimerHandle DestroyTimer;

	UPROPERTY(EditAnywhere)
		float DestroyTime = 3.f;
};
