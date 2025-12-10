// Fill out your copyright notice in the Description page of Project Settings.


#include "EndLevelGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UnlimitedGameMode.h"
#include "SpaceshipPawn.h"

void AEndLevelGameMode::BeginPlay()
{
	myPawn = UGameplayStatics::GetPlayerPawn(this, 0); //Gets the current pawn on the level, with player controller 0.
	myPawn->DisableInput(UGameplayStatics::GetPlayerController(this, 0)); //Disables the input for the player.
}
