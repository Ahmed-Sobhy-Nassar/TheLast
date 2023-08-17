	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TheLast/HUD/BlasterHUD.h"
#include "TheLast/Weapon/WeaponTypes.h"
#include "TheLast/BlasterTypes/CombatState.h"
#include "CombatComponent.generated.h"

#define TRACE_LENGTH 800.f // for the Future Change it to range for each weapon make it UPROPERTY and change it from the BP Class 
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THELAST_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCombatComponent();
	friend class ABlasterCharacter;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void EquipWeapon(class AWeapon* WeaponToEquip);
	void Reload();
	UFUNCTION(BlueprintCallable)
		void FinishReloading();
	void FireButtonPressed(bool bPressed);

protected:
	virtual void BeginPlay() override;
	void SetAiming(bool bIsAiming);
	void SetSprint(bool bIsSprinting);

   
	UFUNCTION(Server, Reliable)
		void ServerSetAiming(bool bIsAiming);

	UFUNCTION(Server, Reliable)
		void ServerSetSprinting(bool bIsSprinting);

	UFUNCTION()
		void OnRep_EquippedWeapon();

	

	void Fire();

	UFUNCTION(Server, Reliable)
		void ServerFire(const FVector_NetQuantize& TraceHitTarget);
	UFUNCTION(NetMulticast, Reliable)
		void MulticastFire(const FVector_NetQuantize& TraceHitTarget);
	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

	void SetHUDCrosshairs(float DeltaTime);

	UFUNCTION(Server, Reliable)
		void ServerReload();

	void HandleReload();

	int32 AmountToReload();

private:
	UPROPERTY()
	class ABlasterCharacter* Character;
	UPROPERTY()
	class ABlasterPlayerController* Controller;
	UPROPERTY()
	class ABlasterHUD* HUD;
	// why making EquippedWeapon using OnRep_EquippedWeapon simply becasue it's already replicated so the game doesn't use more Bandwidth means less lagging		
	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
		AWeapon* EquippedWeapon;

	UPROPERTY(Replicated)
		bool bAiming;
	UPROPERTY(Replicated)
		bool bSprinting;

	UPROPERTY(EditAnywhere)
		float BaseWalkSpeed;
	UPROPERTY(EditAnywhere)
		float SprintWalkSpeed;

	UPROPERTY(EditAnywhere)
		float AimWalkSpeed;

	bool bFireButtonPressed;

	// HUD and Crosshairs
	float CrosshairVelocityFactor;
	float CrosshairInAirFactor;
	float CrosshairAimFactor;
	float CrosshairSprintFactor;
	float CrosshairShootingFactor;

	FVector HitTarget; 
	FHUDPackage HUDPackage;

	/**
	* Aiming and FOV
	*/

	// Field of view when not aiming; set to the camera's base FOV in BeginPlay
	float DefaultFOV;

	UPROPERTY(EditAnywhere, Category = Combat)
		float ZoomedFOV = 30.f;
	float CurrentFOV;
	UPROPERTY(EditAnywhere, Category = Combat)
		float ZoomInterpSpeed = 20.f;
	void InterpFOV(float DeltaTime); // set the FOV (Field of view) 

	/**
	* Automatic fire
	*/
	FTimerHandle FireTimer;
	bool bCanFire = true;
	void StartFireTimer();
	void FireTimerFinished();
	bool CanFire();

	// Carried ammo for the currently-equipped weapon
	
	UPROPERTY(ReplicatedUsing = OnRep_CarriedAmmo)
		int32 CarriedAmmo;


	UFUNCTION()
		void OnRep_CarriedAmmo();

	TMap<EWeaponType, int32> CarriedAmmoMap; // back to lecture 115 

	UPROPERTY(EditAnywhere)
		int32 StartingARAmmo = 30;

	UPROPERTY(EditAnywhere)
		int32 StartingRocketAmmo = 0;

	void InitializeCarriedAmmo();

	 

	// lec 118
	UPROPERTY(ReplicatedUsing = OnRep_CombatState)
		ECombatState CombatState = ECombatState::ECS_Unoccupied;

	UFUNCTION()
		void OnRep_CombatState();

	void UpdateAmmoValues();



public:

};