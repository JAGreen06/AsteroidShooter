// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlimitedGameMode.h"
#include "Asteroid.h"
#include "CustomPlayerController.h"
#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

AUnlimitedGameMode::AUnlimitedGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUnlimitedGameMode::GetTime(FTimerHandle& timer)
{
	//Gets the current time of the game.
	timer = GameDurationTimer; 
}

void AUnlimitedGameMode::GetPoints(int& points)
{
	//Gets the current points in the game.
	points = PointsScored;
}

void AUnlimitedGameMode::ScorePoints()
{
	//Scores Points.
	PointsScored++;
	GameInstanceRef->unlimitedScore = PointsScored; //Stores current points in the game instance.
}

void AUnlimitedGameMode::BeginPlay()
{
	GameInstanceRef = Cast<UMainGameInstance>(GetGameInstance()); //Safety Cast to MainGameInstance.

	AddAsteroids(); //Calls Spawn Asteroids function.

	GetWorld()->GetTimerManager().SetTimer(GameDurationTimer, this, &AUnlimitedGameMode::TimerEnded, GameDuration, false); //Creates A timer for the gamemode with duration of 1 minute.
}


void AUnlimitedGameMode::AddAsteroids()
{
	FVector SpawnLocation(0.0f, 0.0f, 0.0f); //Spawn location Declared.

	for (int i = 0; i < NumOfAsteroids; i++) //Spawns 500 Asteroids.
	{
		/*
		* for each asteroid that is spawned a random X, Y, Z value is generated
		* We then add on the spaceshipOffset value to stop asteroids from spawning 
		* near the spaceship when spawning.
		*/
		SpawnLocation.X = FMath::RandRange(MinimumValue, MaximumValue) + SpaceshipOffset;
		SpawnLocation.Y = FMath::RandRange(MinimumValue, MaximumValue) + SpaceshipOffset;
		SpawnLocation.Z = FMath::RandRange(MinimumValue, MaximumValue) + SpaceshipOffset;


		FRotator SpawnRotation(0.0f, 0.0f, 0.0f); //Default (No) Rotation.

		if (asteroids != nullptr) //Safety prevents crash.
		{
			AAsteroid* newAsteroid = GetWorld()->SpawnActor<AAsteroid>(asteroids, SpawnLocation, SpawnRotation); //Spawn in the asteroid. with the parameters created above.
		}
	}
}

void AUnlimitedGameMode::TimerEnded()
{
	GameEnd(true); //Game ended.
}

void AUnlimitedGameMode::GameEnd(bool win)
{
	if (win) 
	{
		UGameplayStatics::OpenLevel(GetWorld(), "WinUnlimLevel"); //Switch to 'win' screen.
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), "FailLevel"); //Switch to 'fail' screen.
	}
}

void AUnlimitedGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}