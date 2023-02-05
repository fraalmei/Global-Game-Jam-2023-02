// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Obstacles/ObstacleActor.h"
#include "Camera/CameraComponent.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"
#include "MyPlayer.generated.h"

UCLASS()
class GAMEJAM_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 Health = 7;


	bool bCanBeDamaged;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 GetPlayerHealth() { return (Health); };
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void	MoveHorizontal(float Amount);

	void	MoveJump();
	void	EnableCrouch();
	void	DisableCrouch();

	UFUNCTION()
	int32	TakePlayerDamage();

	void	ResetPlayerHealth() { Health = 10; };

	UFUNCTION()
		void	HitPlayer();

	UFUNCTION()
	bool	HasBeenHit();
	void	ResetBeenHit();
	bool	bHasBeenHit;
	UFUNCTION()
		virtual void NotifyActorBeginOverlap(AActor* Actor) override;

	UCameraComponent* CameraComponent;

	void	DisableCamera();
	 UFUNCTION()
	void	ResetDamage();

	 UPROPERTY(EditAnywhere, Category = "Sound")
		 TArray<USoundWave*> DamageSounds;
	 UPROPERTY(EditAnywhere, Category = "Sound")
		 TArray<USoundWave*> DeathSounds;
	 UPROPERTY(EditAnywhere, Category = "Sound")
		 TArray<USoundWave*> JumpSounds;

	 USoundWave* GetSoundFromArr(TArray<USoundWave*> Array);

	 UAudioComponent* AudioComponent;

	 void	PlaySound(TArray<USoundWave*> Array);
};
