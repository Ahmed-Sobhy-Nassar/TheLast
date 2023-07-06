// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THELAST_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDScore(float Score);
	void SetHUDDefeats(int32 Defeats);
	void SetHUDWeaponAmmo(int32 Ammo);
	void SetHUDCarriedAmmo(int32 Ammo);
	void SetHUDMatchCountdown(float CountdownTime);
	void SetHUDAnnouncementCountdown(float CountdownTime); //{code 129}
	virtual void OnPossess(APawn* InPawn) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual float GetServerTime(); // Synced with server world clock
	virtual void ReceivedPlayer() override; // Sync with server clock as soon as possible
	
	void OnMatchStateSet(FName State);
	
	void HandleMatchHasStarted();
	void HandleCooldown();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetHUDTime();
	void PollInit(); // Poll the Value of the cashed ones to the CharacterOverlay HUD 


	/**
	* Sync time between client and server
	*/
	
	// Requests the current server time, passing in the client's time when the request was sent
	UFUNCTION(Server, Reliable)
		void ServerRequestServerTime(float TimeOfClientRequest);

	// Reports the current server time to the client in response to ServerRequestServerTime
	UFUNCTION(Client, Reliable)
		void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);

	float ClientServerDelta = 0.f; // difference between client and server time

	UPROPERTY(EditAnywhere, Category = Time)
		float TimeSyncFrequency = 5.f;      

	float TimeSyncRunningTime = 0.f;
	void CheckTimeSync(float DeltaTime);
	 
	// {code 129}
	UFUNCTION(Server, Reliable)
		void ServerCheckMatchState();

	//Handled syncing time between server and clients for the match states as a warmup time match time. 
	//it's OKAY if we do a client with RPC here because we just send it once so we can send that huge amount of data 
	UFUNCTION(Client, Reliable)
		void ClientJoinMidgame(FName StateOfMatch, float Warmup, float Match, float Cooldown, float StartingTime);



private:
	UPROPERTY()
	class ABlasterHUD* BlasterHUD;
	
	UPROPERTY()
		class ABlasterGameMode* BlasterGameMode;
	uint32 CountdownInt = 0;

	float LevelStartingTime = 0.f;
	float MatchTime = 180.f;
	float CooldownTime = 0.f;
	float WarmupTime = 0.f;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
		FName MatchState;

	UFUNCTION()
		void OnRep_MatchState();

	UPROPERTY()
		class UCharacterOverlay* CharacterOverlay;
	bool bInitializeCharacterOverlay = false;

	// Cashed value for the HUD, since they will be Invalid  at the beging because the CharcterOVerlay HUD wont be Initialized at the beginning 
	float HUDHealth;
	float HUDMaxHealth;
	float HUDScore;
	int32 HUDDefeats;
};
