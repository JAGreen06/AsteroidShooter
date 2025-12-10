// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UProjectileMovementComponent;

UCLASS()
class ASTEROIDSHOOTER_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Bullet Properties.
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 5000.0f;
	UPROPERTY()
	float BulletDamage = 10.0f;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BulletMesh;
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* BulletProjectile;

	
	UFUNCTION() //Detects for hitting an actor in the world.
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
