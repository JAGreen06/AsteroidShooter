// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "AsteroidGameModeBase.h"
#include "UnlimitedGameMode.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialise Mesh
	asteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Asteroid Mesh"));
	asteroidMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	//Casting to our gamemode classes. 
	GameModeRef = Cast<AAsteroidGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())); 
	UnlimGameModeRef = Cast<AUnlimitedGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

float AAsteroid::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	AsteroidHealth -= DamageAmount; //Removes the asteroids max health by the amount of damge the bullet did.
	if (AsteroidHealth <= 0) //if asteroid has no health
	{

		//Score Points in the respective Gamemode.
		if (GameModeRef != nullptr)
		{
			GameModeRef->PointScored();
		}
		if (UnlimGameModeRef != nullptr)
		{
			UnlimGameModeRef->ScorePoints();
		}
		
		Destroy(); //Destroy the asteroid.
	}
	return DamageAmount; //Return the amount of damage the bullet did.
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

