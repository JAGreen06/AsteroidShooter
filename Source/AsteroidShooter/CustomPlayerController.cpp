// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "AsteroidGameModeBase.h"
#include "UnlimitedGameMode.h"
#include "MainGameInstance.h"
#include "SpaceshipPawn.h"
#include "Kismet/GameplayStatics.h"

void ACustomPlayerController::BeginPlay()
{
	//Casting for gamemodes and instance to my specific classes.
	GameModeRef = Cast<AAsteroidGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	UnlimGameModeRef = Cast<AUnlimitedGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameInstanceRef = Cast<UMainGameInstance>(GetGameInstance());


	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpaceshipPawn::StaticClass(), FoundActors); //Returns all instances of the spaceshipPawn that are found within a level.


	/* 
	* If there are two instances of a spaceship on a level 
	* then we get the instances of those spaceships stored in the 
	* TArray and assign them to seperate pawns.
	*/
	if (FoundActors.Num() >= 2) 
	{
		pawn1 = Cast<APawn>(FoundActors[0]);
		pawn2 = Cast<APawn>(FoundActors[1]);
	}

	LevelName = GetWorld()->GetMapName(); //Gets the level name, comes with ugly prefix so we use .contains to find the actual level.


	/*
	* The Large if statement below is used for the UI on each level of the game,
	* for each level we determine what level it is, create its designated UUserWidget
	* and then add it to the viewport. We also include the showmouse cursor for levels that function specifically
	* as a menu system.
	*/

	if (LevelName.Contains("MenuLevel"))
	{
		SetShowMouseCursor(true);
		//MENU
		MENU = CreateWidget(this, MenuClass);
		if (MENU != nullptr)
		{
			MENU->AddToViewport();
		}
	}
	else if (LevelName.Contains("FailLevel"))
	{
		SetShowMouseCursor(true);
		//RESTART
		RESTART = CreateWidget(this, RestartClass);
		if (RESTART != nullptr)
		{
			RESTART->AddToViewport();
		}
	}	
	else if (LevelName.Contains("SelectLevel"))
	{
		SetShowMouseCursor(true);
		//SELECT
		SELECT = CreateWidget(this, SelectClass);
		if (SELECT != nullptr)
		{
			SELECT->AddToViewport();
		}
	}
	else if (LevelName.Contains("WinLevel"))
	{
		SetShowMouseCursor(true);
		//WIN
		WIN = CreateWidget(this, WinClass);
		if (WIN != nullptr)
		{
			WIN->AddToViewport();
		}
	}
	else if (LevelName.Contains("InstructionLevel"))
	{
		SetShowMouseCursor(true);
		//WIN
		INSTRUCTIONS = CreateWidget(this, InstructionClass);
		if (INSTRUCTIONS != nullptr)
		{
			INSTRUCTIONS->AddToViewport();
		}
	}
	else if (LevelName.Contains("WinUnlimLevel"))
	{
		SetShowMouseCursor(true);
		//WIN UNLIMITED
		UNLIMITEDWIN = CreateWidget(this, UnlimitedWinClass);
		if (UNLIMITEDWIN != nullptr)
		{
			UNLIMITEDWIN->AddToViewport();
		}
	}
	else if (LevelName.Contains("UnlimitedLevel"))
	{
		SetShowMouseCursor(false);
		//UNLIMITED GAMEPLAY
		UNLIMITED = CreateWidget(this, UnlimitedClass);
		if (UNLIMITED != nullptr)
		{
			UNLIMITED->AddToViewport();
		}
	}
	else
	{
		SetShowMouseCursor(false);
		//HUD
		HUD = CreateWidget(this, HUDClass);
		if (HUD != nullptr)
		{
			HUD->AddToViewport();
		}
	}
}


//Returns the current fuel for the player.
float ACustomPlayerController::GetFuel()
{
	GameModeRef->GetFuel(FuelAmount);
	return FuelAmount;
}

//Returns the amount of bullets the player has left.
int ACustomPlayerController::GetBullets()
{
	GameModeRef->GetBullets(BulletAmount);
	return BulletAmount;
}

//Returs timeleft on each level of the game.
float ACustomPlayerController::GetRemainingTime()
{
	GameModeRef->GetTimerDuration(Timer);
	return GetWorld()->GetTimerManager().GetTimerRemaining(Timer);
}

//Returns the time left on the unlimited Gamemode.
float ACustomPlayerController::GetTimePassed()
{
	UnlimGameModeRef->GetTime(ElapsedTime);
	return GetWorld()->GetTimerManager().GetTimerRemaining(ElapsedTime);
}

//Gets the points to display to the screen.
int ACustomPlayerController::GetPoints()
{
	if (UnlimGameModeRef != nullptr)
	{
		UnlimGameModeRef->GetPoints(Points);
	}
	return Points;
}

//Returns the value of the points that has been stored in the game instance class.
int ACustomPlayerController::GetTotalPoints()
{
	return GameInstanceRef->unlimitedScore;
}

//Called when Z key is pressed, switches the possesion of each pawn.
void ACustomPlayerController::SwitchPawn()
{
	if (switched == true)
	{
		Possess(pawn1);
		switched = false;
	}
	else
	{
		Possess(pawn2);
		switched = true;
	}
}


