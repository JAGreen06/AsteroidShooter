// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDSHOOTER_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public: 
	
	/*
	* Game Instance is active when switching between levels and gamemodes when not destroyed.
	* I use it here to have the score for the timetrial displayed on a seperate screen 
	* as it has a different gamemode and level associated with it.
	*/
	UPROPERTY()
	int unlimitedScore = 0;  //score variable.

};
