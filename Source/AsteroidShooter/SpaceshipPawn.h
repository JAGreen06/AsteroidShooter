// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Bullet.h"
#include "SpaceshipPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UFloatingPawnMovement;
class AAsteroidGameModeBase;
class AUnlimitedGameMode;
class ACustomPlayerController;

UCLASS()
class ASTEROIDSHOOTER_API ASpaceshipPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceshipPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//Ship Setup Variables.
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* spaceshipMesh;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* spaceshipArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* spaceshipCam;
	

	//Ship Movement Variables.
	UPROPERTY(EditAnywhere)
	UInputMappingContext* SpaceshipMappingContext;
	UPROPERTY(EditAnywhere)
	UInputAction* MoveForwardAction;
	UPROPERTY(EditAnywhere)
	UInputAction* LookUpAction;
	UPROPERTY(EditAnywhere)
	UInputAction* RollAction;
	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* MovementComponent;
	UPROPERTY(EditAnywhere)
	float RotationOffset = 4.0f;
	UPROPERTY()
	float MoveSpeed = 1000.0f;
	UPROPERTY()
	float FuelLeft;


	//Fire Variables.
	UPROPERTY(EditAnywhere)
	UInputAction* FireAction;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABullet> BulletClass;
	UPROPERTY(EditAnywhere)
	UInputAction* ReloadAction;

	//Bullet Variables.
	UPROPERTY()
	int BulletCount = 15;
	UPROPERTY(EditAnywhere)
	USoundBase* shootSound;

	//Switch Pawn.
	UPROPERTY(EditAnywhere)
	UInputAction* SwitchAction;
	
	//References
	UPROPERTY()
	AAsteroidGameModeBase* GameModeRef;
	UPROPERTY()
	ACustomPlayerController* PlayerRef;
	UPROPERTY()
	AUnlimitedGameMode* UnlimGameModeRef;


	//Movement Functions.
	void MoveForwardHandler(const FInputActionValue& Value);
	void LookUpHandler(const FInputActionValue& Value);
	void RollHandler(const FInputActionValue& Value);

	//Switch Pawn Handler.
	void SwitchHandler(const FInputActionValue& Value);


	//Fire Handler.
	void FireHandler(const FInputActionValue& Value);
	void ReloadHandler(const FInputActionValue& Value);

	//Collision Handler.
	UFUNCTION()
	void OnSpaceshipCollision(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
