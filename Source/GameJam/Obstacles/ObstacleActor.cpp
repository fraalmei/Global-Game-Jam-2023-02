// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleActor.h"

// Sets default values
AObstacleActor::AObstacleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstacleActor::BeginPlay()
{
	Super::BeginPlay();
	Movement = 10;
	InitialZPosition = GetActorLocation().X;
}

// Called every frame
void AObstacleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if  (AnimationZ == 0.f)
			SetActorLocation(GetActorLocation() + FVector(-MovementSpeed, 0.f, 0.f));
	else
	{
		if (GetActorLocation().Z == AnimationZ)
		{
			Movement = 0;
		}
		else if (GetActorLocation().Z == InitialZPosition)
		{
			Movement = 1;
		}
		SetActorLocation(GetActorLocation() + FVector(-MovementSpeed, 0.f, Movement));
	}
	if (GetActorLocation().X < 220)
		Destroy();
}

