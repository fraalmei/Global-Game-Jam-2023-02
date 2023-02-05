// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AMyGameModeBase::AMyGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	EasyDifficulty();

	bHasSpawnedLeftWall = false;
	bHasSpawnedRightWall = false;

	InitObstactleSpawn();

	Miles = 0;
	Stage = 1;

	AudioComponent = FindComponentByClass<UAudioComponent>();
	Player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	HUD = Cast<AMyHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (MainWidgetClass)
	{
		if (UGameplayStatics::GetPlayerController(GetWorld(), 0))
			MainWidget = CreateWidget<UMyUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MainWidgetClass);
		MainWidget->AddToViewport();
		if (Player)
			MainWidget->SetPlayerHealthText(Player->GetPlayerHealth());
		MainWidget->ToggleRedScreen(false);
		MainWidget->ToggleYouLoseScreen(false);
		MainWidget->ToggleHealthDistanceText(false);
		MainWidget->ToggleStoryScreen(false);
	}
	if (MusicSound)
		PlaySound(MusicSound);
	//Speed = 20.f;
	//if (UGameplayStatics::GetPlayerController(GetWorld(), 0))
		//UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
}

void AMyGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Stage == 1)
	{
		Speed = 0;

		if (MainWidget)
		{
			MainWidget->ToggleRedScreen(false);
			MainWidget->ToggleYouLoseScreen(false);
			MainWidget->ToggleHealthDistanceText(false);
			MainWidget->ToggleStoryScreen(true);
		}
		if (StoryMessage == "Vacio")
		{
			StoryMessage = "Lumberjack Ed is on his way to perform\r\n his everyday routine,\r\n hired for just cutting trees...\r\njust trees?";
			LoadStoryText();
			StoryMessage = "Ed tries cutting down a big tree who is gonna provide\r\n a large amount of lumber, but this time the tree,\r\n consumed by all the agony and pain of his fallen \r\nbrothers takes revenge,\r\n the roots are coming for you...";
			FTimerDelegate TimerDel;
			FTimerHandle TimerHandle;
			TimerDel.BindUFunction(this, FName("StartGame"));
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 3.f, false);
			Stage = -1;
		}
		else if (StoryMessage == "End")
		{
			StoryMessage = "The roots are not coming for you anymore,\r\n you stare at the end of the forest, \r\nbadly injured, your axe has turned...red?.";
			LoadStoryText();
			StoryMessage = "You see the ...end?, you were never in a forest,\r\nyou remember everything,this is your punishment,\r\nyour death realm, the forest are the haunted \r\nsouls of the innocent people you've murdered. \r\n\r\nCondemned to be haunted forever, \r\nyou'll pay for your sins, \r\ngame over.";
			FTimerDelegate TimerDel;
			FTimerHandle TimerHandle;
			TimerDel.BindUFunction(this, FName("EndGame"));
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 3.f, false);
			Stage = -1;
		}
		else
		{
			FTimerDelegate TimerDel;
			FTimerHandle TimerHandle;
			TimerDel.BindUFunction(this, FName("StartStage2"));
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 3.f, false);
			Stage = -1;
		}

		return;
	}
	if (Stage == -1)
	{
		return;
	}


	if (!bHasSpawnedLeftWall)
		SpawnLeftWall();
	if (!bHasSpawnedRightWall)
		SpawnRightWall();
	if (!bHasSpawnedObstacleOne)
		SpawnObstacleOne();
	if (!bHasSpawnedObstacleTwo)
		SpawnObstacleTwo();
	if (!bHasSpawnedObstacleThree)
		SpawnObstacleThree();

	if (Player)
	{
		if (MainWidget)
			MainWidget->ToggleHealthDistanceText(true);
		if (Player->GetActorLocation().Z <= -100.f)
		{
			Player->ResetPlayerHealth();
			MainWidget->ToggleYouLoseScreen(true);
			AudioComponent->Stop();
			Speed = 0.f;
			StoryMessage = "End";
			StartStage1();

		}
		if (Player->HasBeenHit())
		{
			Player->HitPlayer();
			if (RootSound)
				UGameplayStatics::PlaySound2D(GetWorld(), RootSound);
			if (Player->TakePlayerDamage() <= 0)
			{
				Player->ResetPlayerHealth();
				AudioComponent->Stop();
				if (MusicSound)
					PlaySound(MusicSound);
				MainWidget->ToggleHealthDistanceText(false);
				Speed = 0.f;
				FTimerDelegate TimerDel;
				FTimerHandle TimerHandle;
				StoryMessage = "End";
				StartStage1();

			}
			if (MainWidget)
			{
				MainWidget->ToggleHealthDistanceText(true);
				MainWidget->SetPlayerHealthText(Player->GetPlayerHealth());
				MainWidget->ToggleRedScreen(true);
				FTimerDelegate TimerDel;
				FTimerHandle TimerHandle;
				TimerDel.BindUFunction(this, FName("ResetRedScreen"));
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 0.08f, false);
			}

			Player->ResetBeenHit();
		}
	}

	if (Miles == 500)
	{
		MedDifficulty();
		if (PlayerBreathLight)
			PlaySound(PlayerBreathLight);
	}
	else if (Miles == 1200)
	{
		HardDifficulty();
		if (PlayerBreath)
			PlaySound(PlayerBreath);
		
	}
	
	if (MainWidget)
		MainWidget->SetDistanceText(Miles);
	Miles++;
}

void AMyGameModeBase::SpawnLeftWall()
{
	WallClass = GetWallFromArr(WallNormal);
	if (IsValid(WallClass))
	{
		UWorld* MyLevel = GetWorld();

		if (IsValid(MyLevel))
		{
			FVector Loc = FVector(2070.f, 440.f, 0.f);
			FRotator Rot = FRotator::ZeroRotator;
			FActorSpawnParameters SpawnParams = FActorSpawnParameters();
			AActorWall* SpawnedActor = Cast<AActorWall>(GetWorld()->SpawnActor(WallClass, &Loc, &Rot, SpawnParams));
			if (SpawnedActor)
				bHasSpawnedLeftWall = true;
			SpawnedActor->SetMovementSpeed(Speed);
			FTimerDelegate TimerDel;
			FTimerHandle TimerHandle;
			TimerDel.BindUFunction(this, FName("ResetLeftWallSpawn"));
			float Time = FMath::RandRange(MinSpawnTime, MaxSpawnTime);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, Time, false);
		}
	}
}

void AMyGameModeBase::SpawnRightWall()
{
	WallClass = GetWallFromArr(WallNormal);
	if (IsValid(WallClass))
	{
		UWorld* MyLevel = GetWorld();

		if (IsValid(MyLevel))
		{
			FVector Loc = FVector(2070.f, 1080.f, 0.f);
			FRotator Rot = FRotator::ZeroRotator;
			FActorSpawnParameters SpawnParams = FActorSpawnParameters();
			AActorWall* SpawnedActor = Cast<AActorWall>(GetWorld()->SpawnActor(WallClass, &Loc, &Rot, SpawnParams));
			if (SpawnedActor)
				bHasSpawnedRightWall = true;
			SpawnedActor->SetMovementSpeed(Speed);
			FTimerDelegate TimerDel;
			FTimerHandle TimerHandle;
			TimerDel.BindUFunction(this, FName("ResetRightWallSpawn"));
			float Time = FMath::RandRange(MinSpawnTime, MaxSpawnTime);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, Time, false);
		}
	}
}

void AMyGameModeBase::ResetLeftWallSpawn()
{
	bHasSpawnedLeftWall = false;
}

void AMyGameModeBase::ResetRightWallSpawn()
{
	bHasSpawnedRightWall = false;
}

void AMyGameModeBase::InitObstactleSpawn()
{
	FTimerDelegate TimerDel1;
	FTimerHandle TimerHandle1;
	FTimerDelegate TimerDel2;
	FTimerHandle TimerHandle2;
	FTimerDelegate TimerDel3;
	FTimerHandle TimerHandle3;
	
	bHasSpawnedObstacleOne = true;
	bHasSpawnedObstacleTwo = true;
	bHasSpawnedObstacleThree = true;

	//Obstacle ONE
	TimerDel1.BindUFunction(this, FName("ResetObstacleOneSpawn"));
	float Time = FMath::RandRange(MinSpawnTimeObstacleOne, MaxSpawnTimeObstacleOne);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle1, TimerDel1, Time, false);

	//Obstacle TWO
	TimerDel2.BindUFunction(this, FName("ResetObstacleTwoSpawn"));
	Time = FMath::RandRange(MinSpawnTimeObstacleTwo, MaxSpawnTimeObstacleTwo);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle2, TimerDel2, Time, false);

	//Obstacle THREE
	TimerDel3.BindUFunction(this, FName("ResetObstacleThreeSpawn"));
	Time = FMath::RandRange(MinSpawnTimeObstacleThree, MaxSpawnTimeObstacleThree);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle3, TimerDel3, Time, false);
}

void AMyGameModeBase::SpawnObstacleOne()
{
	if (IsValid(ObstacleOneClass))
	{
		UWorld* MyLevel = GetWorld();

		if (IsValid(MyLevel))
		{
			float AxisX = FMath::RandRange(2000.f, 2080.f);
			float AxisY = FMath::RandRange(600.f, 970.f);
			FVector Loc = FVector(AxisX, AxisY, 0.f);
			float RotationX = FMath::RandRange(0.f, 35.f);
			float RotationY = FMath::RandRange(0.f, 35.f);
			float RotationZ = FMath::RandRange(0.f, 35.f);
			FRotator Rot = FRotator(RotationX, RotationY, RotationZ);
			FActorSpawnParameters SpawnParams = FActorSpawnParameters();
			AObstacleActor* SpawnedActor = Cast<AObstacleActor>(GetWorld()->SpawnActor(ObstacleOneClass, &Loc, &Rot, SpawnParams));
			if (SpawnedActor)
				bHasSpawnedObstacleOne = true;
			SpawnedActor->SetMovementSpeed(Speed);
			FTimerDelegate TimerDel;
			FTimerHandle TimerHandle;
			TimerDel.BindUFunction(this, FName("ResetObstacleOneSpawn"));
			float Time = FMath::RandRange(MinSpawnTimeObstacleOne, MaxSpawnTimeObstacleOne);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, Time, false);
			
		}
	}
}

void AMyGameModeBase::SpawnObstacleTwo()
{
	if (IsValid(ObstacleTwoClass))
	{
		UWorld* MyLevel = GetWorld();

		if (IsValid(MyLevel))
		{
			float AxisX = FMath::RandRange(2000.f, 2080.f);
			float AxisYSeed = FMath::RandRange(0.f, 10.f);
			float AxisY = 980.f;
			if (AxisYSeed > 5)
				AxisY = 580.f;
			FVector Loc = FVector(AxisX, AxisY, 100.f);
			float RotationX = FMath::RandRange(0.f, 80.f);
			FRotator Rot = FRotator(0.f, 0.f, RotationX);
			FActorSpawnParameters SpawnParams = FActorSpawnParameters();
			AObstacleActor* SpawnedActor = Cast<AObstacleActor>(GetWorld()->SpawnActor(ObstacleTwoClass, &Loc, &Rot, SpawnParams));
			if (SpawnedActor)
				bHasSpawnedObstacleTwo = true;
			SpawnedActor->SetMovementSpeed(Speed);
			FTimerDelegate TimerDel;
			FTimerHandle TimerHandle;
			TimerDel.BindUFunction(this, FName("ResetObstacleTwoSpawn"));
			float Time = FMath::RandRange(MinSpawnTimeObstacleOne, MaxSpawnTimeObstacleOne);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, Time, false);

		}
	}
}

void AMyGameModeBase::SpawnObstacleThree()
{
	if (IsValid(ObstacleThreeClass))
	{
		UWorld* MyLevel = GetWorld();

		if (IsValid(MyLevel))
		{
			float AxisX = FMath::RandRange(2000.f, 2080.f);
			float AxisY = FMath::RandRange(470.f, 1030.f);
			FVector Loc = FVector(AxisX, AxisY, 0.f);
			FRotator Rot = FRotator::ZeroRotator;
			FActorSpawnParameters SpawnParams = FActorSpawnParameters();
			AObstacleActor* SpawnedActor = Cast<AObstacleActor>(GetWorld()->SpawnActor(ObstacleThreeClass, &Loc, &Rot, SpawnParams));
			if (SpawnedActor)
				bHasSpawnedObstacleThree = true;
			SpawnedActor->SetMovementSpeed(Speed);
			FTimerDelegate TimerDel;
			FTimerHandle TimerHandle;
			TimerDel.BindUFunction(this, FName("ResetObstacleThreeSpawn"));
			float Time = FMath::RandRange(MinSpawnTimeObstacleOne, MaxSpawnTimeObstacleOne);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, Time, false);

		}
	}
}

void AMyGameModeBase::ResetObstacleOneSpawn()
{
	bHasSpawnedObstacleOne = false;
}

void AMyGameModeBase::ResetObstacleTwoSpawn()
{
	bHasSpawnedObstacleTwo = false;
}

void AMyGameModeBase::ResetObstacleThreeSpawn()
{
	bHasSpawnedObstacleThree = false;
}

TSubclassOf <AActorWall> AMyGameModeBase::GetWallFromArr(TArray<TSubclassOf<AActorWall>> Arr)
{
	if (Arr.Num() == 0)
		return (nullptr);
	float Num = FMath::RandRange(0, Arr.Num() - 1);

	while (!Arr.IsValidIndex(Num))
	{
		Num = FMath::RandRange(0, Arr.Num() - 1);
	}
	return (Arr[Num]);
}

void AMyGameModeBase::EasyDifficulty()
{
	WallClass = GetWallFromArr(WallNormal);
	ObstacleOneClass = ObstacleOneNormal;
	ObstacleTwoClass = ObstacleTwoNormal;
	ObstacleThreeClass = ObstacleThreeNormal;

	Speed = 20.f;
	BackupSpeed = 20.f;
}

void AMyGameModeBase::MedDifficulty()
{
	WallClass = GetWallFromArr(WallNormal);
	ObstacleOneClass = ObstacleOneNormal;
	ObstacleTwoClass = ObstacleTwoNormal;
	ObstacleThreeClass = ObstacleThreeNormal;

	MinSpawnTimeObstacleOne -= (MinSpawnTimeObstacleOne / 2);
	MaxSpawnTimeObstacleOne -= (MaxSpawnTimeObstacleOne / 2);

	MinSpawnTimeObstacleTwo -= (MinSpawnTimeObstacleTwo / 2);
	MaxSpawnTimeObstacleTwo -= (MaxSpawnTimeObstacleTwo / 2);

	MinSpawnTimeObstacleThree -= (MinSpawnTimeObstacleThree / 2);
	MaxSpawnTimeObstacleThree -= (MaxSpawnTimeObstacleThree / 2);

	Speed = 30.f;
	BackupSpeed = 30.f;
}

void AMyGameModeBase::HardDifficulty()
{
	WallClass = GetWallFromArr(WallNormal);
	ObstacleOneClass = ObstacleOneNormal;
	ObstacleTwoClass = ObstacleTwoNormal;
	ObstacleThreeClass = ObstacleThreeNormal;

	MinSpawnTimeObstacleOne /= 2;
	MaxSpawnTimeObstacleOne /= 2;

	MinSpawnTimeObstacleTwo /= 2;
	MaxSpawnTimeObstacleTwo /= 2;

	MinSpawnTimeObstacleThree /= 2;
	MaxSpawnTimeObstacleThree /= 2;

	Speed = 40.f;
	BackupSpeed = 40.f;
}

void AMyGameModeBase::ResetRedScreen()
{
	if (MainWidget)
		MainWidget->ToggleRedScreen(false);
}

void AMyGameModeBase::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenu"), false);
}

void	AMyGameModeBase::PlaySound(USoundBase* Sound)
{
	if (AudioComponent)
	{
		if (AudioComponent->IsPlaying())
			AudioComponent->Stop();
		AudioComponent->SetSound(Sound);
		AudioComponent->Play();
	}
}

void AMyGameModeBase::StartStage1()
{
	Stage = 1;
	Speed = 0.f;
}

void AMyGameModeBase::StartStage2()
{
	Stage = 2;
	Speed = 20.f;
	MainWidget->ToggleStoryScreen(false);
	if (ChaseSound && AudioComponent)
		PlaySound(ChaseSound);
}

void AMyGameModeBase::LoadStoryText()
{
	if (MainWidget)
	{
		MainWidget->SetStoryText(StoryMessage);
	}
}

void AMyGameModeBase::EndGame()
{
	LoadStoryText();
	Stage = -1;
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;
	TimerDel.BindUFunction(this, FName("YouLoseScreen"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 6.f, false);
}

void AMyGameModeBase::YouLoseScreen()
{
	if (MainWidget)
	{
		MainWidget->ToggleStoryScreen(false);
		MainWidget->ToggleYouLoseScreen(true);
	}
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;
	TimerDel.BindUFunction(this, FName("RestartLevel"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 2.f, false);
}

void AMyGameModeBase::StartGame()
{
	LoadStoryText();
	Stage = 1;
}