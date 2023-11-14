
#pragma once

#include "CoreMinimal.h"
#include "Projecttile.h"
#include "ProjectileBullet.generated.h"

UCLASS()
class THELAST_API AProjectileBullet : public AProjecttile
{
	GENERATED_BODY()

public:
	AProjectileBullet();

protected:
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
