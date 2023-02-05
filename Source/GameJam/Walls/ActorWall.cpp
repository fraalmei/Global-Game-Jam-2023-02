// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorWall.h"

// Sets default values
AActorWall::AActorWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + FVector(-MovementSpeed, 0.f, 0.f));
	if (GetActorLocation().X < 220)
		Destroy();
}

