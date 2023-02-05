 //Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"

// Sets default valuess
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	Health = 10;
	bHasBeenHit = false;
	bCanBeDamaged = true;

	AudioComponent = FindComponentByClass<UAudioComponent>();

}

USoundWave* AMyPlayer::GetSoundFromArr(TArray<USoundWave*> Array)
{
	if (Array.Num() <= 0)
		return (nullptr);
	float Index = FMath::RandRange(0, Array.Num() - 1);

	while (!Array.IsValidIndex(Index))
	{
		Index = FMath::RandRange(0, Array.Num() - 1);
	}
	return (Array[Index]);
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Horizontal", this, &AMyPlayer::MoveHorizontal);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayer::MoveJump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMyPlayer::EnableCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMyPlayer::DisableCrouch);

}

void AMyPlayer::MoveHorizontal(float Amount)
{
	float	Velocity;
	float	WorldUnit;

	Velocity = Amount;
	if (GetMovementComponent())
		Velocity *= GetMovementComponent()->GetMaxSpeed();
	WorldUnit = 1.f;
	if (GetActorLocation().Y + WorldUnit > 970.f && Amount > 0.f)
		return;
	if (GetActorLocation().Y - WorldUnit < 600.f && Amount < 0.f)
		return;
	AddMovementInput(FVector(0.f, Velocity, 0.f));
}

void AMyPlayer::MoveJump()
{

	Jump();
	PlaySound(JumpSounds);
	if (CanJump())
		SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, 80.f));
}

void	AMyPlayer::EnableCrouch()
{
	Crouch();
	SetActorScale3D(GetActorScale3D() + FVector(0.f, 0.f, -0.75f));
}

void	AMyPlayer::DisableCrouch()
{
	UnCrouch();
	SetActorScale3D(GetActorScale3D() + FVector(0.f, 0.f, 0.75f));
}

int32	AMyPlayer::TakePlayerDamage()
{
	if (bCanBeDamaged)
	{
		Health--;
		if (Health <= 0)
			PlaySound(DeathSounds);
		else
			PlaySound(DamageSounds);
		bCanBeDamaged = false;
		FTimerDelegate TimerDel;
		FTimerHandle TimerHandle;
		TimerDel.BindUFunction(this, FName("ResetDamage"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 0.5f, false);
	}


	return (Health);
}

bool	AMyPlayer::HasBeenHit()
{
	return (bHasBeenHit);
}

void	AMyPlayer::ResetBeenHit()
{
	bHasBeenHit = false;
}

void	AMyPlayer::HitPlayer()
{
	UStaticMeshComponent* StaticMesh = FindComponentByClass<UStaticMeshComponent>();
	if (StaticMesh)
	{
		//StaticMesh->AddForce(FVector(120.f, 0.f, 0.f) * StaticMesh->GetMass());
	}
}
void AMyPlayer::NotifyActorBeginOverlap(AActor* Actor)
{
	Super::NotifyActorBeginOverlap(Actor);

	if (Actor->ActorHasTag("Obstacle"))
	{
		bHasBeenHit = true;
	}

}

void	AMyPlayer::DisableCamera()
{
	FindComponentByClass<UCameraComponent>();


}

void	AMyPlayer::ResetDamage() 
{
	bCanBeDamaged = true; 
}

void	AMyPlayer::PlaySound(TArray<USoundWave*> Array)
{
	if (AudioComponent)
	{
		if (AudioComponent->IsPlaying())
			AudioComponent->Stop();
		AudioComponent->SetSound(GetSoundFromArr(Array));
		AudioComponent->Play();
	}
}