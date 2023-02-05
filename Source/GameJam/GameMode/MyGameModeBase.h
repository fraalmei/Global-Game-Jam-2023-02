// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Walls/ActorWall.h"
#include "../Character/MyPlayer.h"
#include "../HUD/MyHUD.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyGameModeBase();
	virtual void Tick(float DeltaSeconds) override;

	AMyPlayer* Player;

	float Speed;
	float BackupSpeed;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase*	PlayerBreath;
	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* PlayerBreathLight;

	UPROPERTY()
		float Miles;
	UPROPERTY()
		int32 Stage;

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Walls")
		TArray<TSubclassOf<AActorWall>> WallNormal;
	UPROPERTY(EditAnywhere, Category = "Walls")
		float	MinSpawnTime = 1.f;
	UPROPERTY(EditAnywhere, Category = "Walls")
		float	MaxSpawnTime = 2.f;
	TSubclassOf<AActorWall> WallClass;
	bool bHasSpawnedLeftWall;
	bool bHasSpawnedRightWall;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UMyUserWidget> MainWidgetClass;
	UMyUserWidget* MainWidget;
	AMyHUD* HUD;

	UFUNCTION()
		TSubclassOf <AActorWall> GetWallFromArr(TArray<TSubclassOf<AActorWall>> Arr);
	UFUNCTION()
	void SpawnLeftWall();
	UFUNCTION()
	void SpawnRightWall();
	UFUNCTION()
	void ResetLeftWallSpawn();
	UFUNCTION()
	void ResetRightWallSpawn();

	UPROPERTY(EditAnywhere, Category = "Obstacles")
		TSubclassOf<AObstacleActor> ObstacleOneNormal;
	UPROPERTY(EditAnywhere, Category = "Obstacles")
		float	MinSpawnTimeObstacleOne = 10.f;
	UPROPERTY(EditAnywhere, Category = "Obstacles")
		float	MaxSpawnTimeObstacleOne = 30.f;

	UPROPERTY(EditAnywhere, Category = "Obstacles")
		TSubclassOf<AObstacleActor> ObstacleTwoNormal;
	UPROPERTY(EditAnywhere, Category = "Obstacles")
		float	MinSpawnTimeObstacleTwo = 1.f;
	UPROPERTY(EditAnywhere, Category = "Obstacles")
		float	MaxSpawnTimeObstacleTwo = 3.f;
	UPROPERTY(EditAnywhere, Category = "Obstacles")
		TSubclassOf<AObstacleActor> ObstacleThreeNormal;
	UPROPERTY(EditAnywhere, Category = "Obstacles")
		float	MinSpawnTimeObstacleThree = 1.f;
	UPROPERTY(EditAnywhere, Category = "Obstacles")
		float	MaxSpawnTimeObstacleThree = 3.f;

	TSubclassOf<AObstacleActor> ObstacleOneClass;
	TSubclassOf<AObstacleActor> ObstacleTwoClass;
	TSubclassOf<AObstacleActor> ObstacleThreeClass;
	bool bHasSpawnedObstacleOne;
	bool bHasSpawnedObstacleTwo;
	bool bHasSpawnedObstacleThree;

	UFUNCTION()
		void SpawnObstacleOne();
	UFUNCTION()
		void ResetObstacleOneSpawn();
	UFUNCTION()
		void SpawnObstacleTwo();
	UFUNCTION()
		void ResetObstacleTwoSpawn();
	UFUNCTION()
		void SpawnObstacleThree();
	UFUNCTION()
		void ResetObstacleThreeSpawn();
	UFUNCTION()
		void InitObstactleSpawn();
	UFUNCTION()
		void EasyDifficulty();

	void	MedDifficulty();

	void	HardDifficulty();

	UFUNCTION()
		void ResetRedScreen();
	UFUNCTION()
		void RestartLevel();

	UAudioComponent* AudioComponent;

	void	PlaySound(USoundBase* Sound);

	
	FString StoryMessage = "Vacio";

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* RootSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* MusicSound;;
	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* ChaseSound;;
	UFUNCTION()
		void LoadStoryText();
	UFUNCTION()
		void StartStage1();
	UFUNCTION()
		void StartStage2();
	UFUNCTION()
		void EndGame();
	UFUNCTION()
		void YouLoseScreen();
	UFUNCTION()
		void StartGame();
};
