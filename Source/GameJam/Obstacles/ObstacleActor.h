// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleActor.generated.h"

UCLASS()
class GAMEJAM_API AObstacleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementSpeed = 20.f;

	void SetMovementSpeed(float Speed) { MovementSpeed = Speed; }
	UPROPERTY(EditAnywhere, Category = "Movement")
		float AnimationZ = 0.f;

	float Movement;
	float InitialZPosition;
};
