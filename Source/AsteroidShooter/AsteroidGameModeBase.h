// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Asteroid.h"
#include "AsteroidGameModeBase.generated.h"



UCLASS()
class ASTEROIDSHOOTER_API AAsteroidGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public: 
	//Points Scoring
	UFUNCTION()
	void PointScored();


	//End Game Function
	UFUNCTION()
	void GameOver(bool valid);


	//Fuel Functions
	UFUNCTION()
	void FuelDrain();
	UFUNCTION() 
	void GetFuel(float& fuel);
	UFUNCTION()
	void AddFuel();


	//Reload Functions
	UFUNCTION()
	void ReloadBullets();
	UFUNCTION()
	void GetBullets(int& bullets);
	UFUNCTION()
	void FireBullet();


	//Timer
	void GetTimerDuration(FTimerHandle& timer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:

	//Point Properties
	UPROPERTY()
	int Points = 0;
	UPROPERTY()
	int PointsMax = 5;


	//Fuel Properties
	UPROPERTY()
	float FuelMax = 100.0f;
	UPROPERTY()
	float FuelAdd = 50.0f;
	UPROPERTY()
	float FuelRemainder = 0.0f;
	UPROPERTY(EditAnywhere)
	float FuelDrainModifier = 0.1f;


	//Reloading
	UPROPERTY(EditAnywhere)
	int BulletMax = 15;
	UPROPERTY()
	int BulletCount = BulletMax;


	//Timer Properties
	UPROPERTY()
	FTimerHandle GameDurationTimer;
	UPROPERTY()
	float GameDuration = 30.0f;
	UPROPERTY()
	float RemainingTime;


	//Level Management
	UPROPERTY()
	FString NextLevelName;
	UPROPERTY()
	FString	LevelName;
	

	//Functions
	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void TimeUp();
	UFUNCTION()
	void LoadNextLevel();
	UFUNCTION()
	void RestartCurrentLevel();
};
