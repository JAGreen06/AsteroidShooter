// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */

class UUserWidget;
class AAsteroidGameModeBase;
class AUnlimitedGameMode;
class ASpaceshipPawn;
class UMainGameInstance;

UCLASS()
class ASTEROIDSHOOTER_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SwitchPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
private: 

	UPROPERTY()
	FString LevelName;


	//UI Setup
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;
	UPROPERTY()
	UUserWidget* HUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MenuClass;
	UPROPERTY()
	UUserWidget* MENU;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> RestartClass;
	UPROPERTY()
	UUserWidget* RESTART;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SelectClass;
	UPROPERTY()
	UUserWidget* SELECT;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinClass;
	UPROPERTY()
	UUserWidget* WIN;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> InstructionClass;
	UPROPERTY()
	UUserWidget* INSTRUCTIONS;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> UnlimitedClass;
	UPROPERTY()
	UUserWidget* UNLIMITED;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> UnlimitedWinClass;
	UPROPERTY()
	UUserWidget* UNLIMITEDWIN;

	// Fuel-Bullets-Timer-Points Functions.
	UFUNCTION(BlueprintPure)
	float GetFuel();
	UFUNCTION(BlueprintPure)
	int GetBullets();
	UFUNCTION(BlueprintPure)
	float GetRemainingTime();
	UFUNCTION(BlueprintPure)
	float GetTimePassed();
	UFUNCTION(BlueprintPure)
	int GetPoints(); //AsteroidGameMode.
	UFUNCTION(BlueprintPure)
	int GetTotalPoints(); //UnlimitedGameMode.


	//Bullet-Fuel-Timer-Points Properties. 
	UPROPERTY()
	int BulletAmount;
	UPROPERTY(EditAnywhere)
	float FuelAmount;
	UPROPERTY()
	FTimerHandle Timer;
	UPROPERTY()
	FTimerHandle ElapsedTime;
	UPROPERTY()
	int Points;
	UPROPERTY()
	int MaxPoints;

	//Pawn Possesion.
	UPROPERTY()
	APawn* pawn1;
	UPROPERTY()
	APawn* pawn2;
	UPROPERTY()
	bool switched = true;
	UPROPERTY()
	TArray<AActor*> FoundActors; //Array of actors in a level.


	//Gamemode references.
	UPROPERTY()
	AAsteroidGameModeBase* GameModeRef;
	UPROPERTY()
	AUnlimitedGameMode* UnlimGameModeRef;

	//Game Instance ref.
	UPROPERTY()
	UMainGameInstance* GameInstanceRef;
};
