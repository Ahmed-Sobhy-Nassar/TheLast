#include "ProjectileBullet.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TheLast/Weapon/Weapon.h"
#include "TheLast/BlasterComponent/CombatComponent.h"

AProjectileBullet::AProjectileBullet()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->SetIsReplicated(true);

	if(FiringWeapon)
		UE_LOG(LogTemp, Warning, TEXT("Hello From Combat"));

}

void AProjectileBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Range = GetActorLocation().X;
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if(!FiringWeapon)
		UE_LOG(LogTemp, Warning, TEXT("Hello From Damage"));
	if (Combate)
		UE_LOG(LogTemp, Warning, TEXT("Hello From Combat"));

	if (FiringWeapon && Range > FiringWeapon->GetRange())
		Damage = 0.f;
	if (OwnerCharacter)
	{
		AController* OwnerController = OwnerCharacter->Controller;
		if (OwnerController )
		{
			
			UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerController, this, UDamageType::StaticClass());
		}
	}
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}