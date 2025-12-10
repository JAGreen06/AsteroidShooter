// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FuelBarrel.generated.h"

class USphereComponent;
class AAsteroidGameModeBase;
class USpinComponent;

UCLASS()
class ASTEROIDSHOOTER_API AFuelBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuelBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 

	//Barrel Properties. 
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BarrelMesh;
	UPROPERTY() 
	USphereComponent* CollisionSphere;

	//Custom Spin Component.
	UPROPERTY(EditAnywhere)
	USpinComponent* SpinBarrel;
	
	//Amount of fuel.
	UPROPERTY()
	float FuelAmount = 100.0f;
	
	//Gamemode refrence.
	UPROPERTY()
	AAsteroidGameModeBase* GameModeRef;


	UFUNCTION() //Overlapping with barrel check function.
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() //Finished Overlapping with barrel check function.
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
