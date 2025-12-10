// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnlimitedGameMode.generated.h"

class AAsteroid;
class UMainGameInstance;

UCLASS()
class ASTEROIDSHOOTER_API AUnlimitedGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void GetTime(FTimerHandle& timer); //Gets the current time of the game.
	UFUNCTION()
	void GetPoints(int& points); //Gets the current points for the game.
	UFUNCTION()
	void ScorePoints(); //Increments players points by 1.
	UFUNCTION()
	void GameEnd(bool win); //Switches level depending on if the player 'wins' or 'loses'.

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	AUnlimitedGameMode();

	virtual void Tick(float DeltaTime) override;
private:

	
	UFUNCTION()
	void AddAsteroids(); //Asteroid Spawning Function.

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAsteroid> asteroids; //Holds all the asteroids spawned.


	//Asteroid Spawning Parameters.
	UPROPERTY(EditAnywhere)
	float MinimumValue = -5000.0f;
	UPROPERTY(EditAnywhere)
	float MaximumValue = 5000.0f;
	UPROPERTY(EditAnywhere)
	float SpaceshipOffset = 100.0f;
	UPROPERTY(EditAnywhere)
	int NumOfAsteroids = 500;

	//Points
	UPROPERTY()
	int PointsScored = 0;

	//Time Handling.
	UPROPERTY()
	FTimerHandle GameDurationTimer;
	UPROPERTY()
	float GameDuration = 60.0f;
	UFUNCTION()
	void TimerEnded();

	
	UPROPERTY()
	UMainGameInstance* GameInstanceRef; //Reference to GameInstance.

};
