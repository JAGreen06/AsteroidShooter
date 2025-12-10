// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

class USphereComponent;
class AAsteroidGameModeBase;
class AUnlimitedGameMode;

UCLASS()
class ASTEROIDSHOOTER_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override; //Take Damage function used, for processing on hit function in bullet. 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Asteroid Properties.
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* asteroidMesh;
	UPROPERTY()
	float AsteroidHealth = 30.0f;


	//GameMode References.
	UPROPERTY()
	AAsteroidGameModeBase* GameModeRef;
	UPROPERTY()
	AUnlimitedGameMode* UnlimGameModeRef;
};
