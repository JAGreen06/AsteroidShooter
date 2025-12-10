// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceshipPawn.h"

void AAsteroidGameModeBase::PointScored() //Scores a point for the player. 
{
	Points++; //Increment

	if (Points == PointsMax) //If we reach the max score.
	{
		LoadNextLevel(); //Loads next level.
	}
}

void AAsteroidGameModeBase::GameOver(bool fail)
{
	if (fail == true)
	{
		//Fail Screen.
		UGameplayStatics::OpenLevel(GetWorld(), "FailLevel");
	}
	else
	{
		//Win Screen.
		UGameplayStatics::OpenLevel(GetWorld(), "WinLevel");
	}
}

void AAsteroidGameModeBase::FuelDrain()
{
	//Takes away player fuel when moving.
	FuelMax = FuelMax - FuelDrainModifier;
}

void AAsteroidGameModeBase::GetFuel(float& fuel)
{
	//Returns the players fuel.
	fuel = FuelMax;
}

void AAsteroidGameModeBase::AddFuel()
{
	//Adds 50 fuel if able to if not adds on the required amount to reach 100.
		if (FuelMax + FuelAdd <= 100.0f)
		{
			FuelMax += FuelAdd;
		}
		else //Prevents playersmax fuel from exceeding 100.0f.
		{
			FuelRemainder = 100.0f - FuelMax;
			FuelMax += FuelRemainder;
		}
}

void AAsteroidGameModeBase::ReloadBullets()
{
	//Bullet Reset.
	BulletCount = BulletMax;
}

void AAsteroidGameModeBase::GetBullets(int& bullets)
{
	//Gets Current Bullets.
	bullets = BulletCount;
}

void AAsteroidGameModeBase::FireBullet()
{
	//Takes away bullet.
	BulletCount--;
}

void AAsteroidGameModeBase::GetTimerDuration(FTimerHandle& timer)
{
	//Returns time.
	timer = GameDurationTimer;
}

void AAsteroidGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	StartGame();
}

void AAsteroidGameModeBase::StartGame()
{
	LevelName = GetWorld()->GetMapName(); //Returns ugly prefix, use .contains for levels.

	if (LevelName.Contains("Level1")) //Level 1 Parameters
	{
		PointsMax = 5;
		GameDuration = 30.0f;
		NextLevelName = "Level2";
	}
	if (LevelName.Contains("Level2")) // Level 2 Parameters
	{
		PointsMax = 10;
		GameDuration = 45.0f;
		NextLevelName = "Level3";
	}
	if (LevelName.Contains("Level3")) // Level 4 Parameters
	{
		PointsMax = 15;
		GameDuration = 60.0f;
		NextLevelName = "WinLevel";
	}

	GetWorld()->GetTimerManager().SetTimer(GameDurationTimer, this, &AAsteroidGameModeBase::TimeUp, GameDuration, false); //Creates timer with duration set in level pararmeters.
}

void AAsteroidGameModeBase::LoadNextLevel()
{
	if (NextLevelName == "WinLevel")
	{
		GameOver(false); //Win Level Opens.
	}
	else
	{
		Points = 0;
		FuelMax = 100.0f;
		UGameplayStatics::OpenLevel(GetWorld(), FName(*NextLevelName)); //Loads the next level for the game, Dereference the fstring to use in OpenLevel.
	}
}

void AAsteroidGameModeBase::RestartCurrentLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName)); //Reopens Current Level.
}

void AAsteroidGameModeBase::TimeUp()
{
	GameOver(true); //Game Lost
}

