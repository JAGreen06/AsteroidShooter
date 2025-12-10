// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceshipPawn.h"
#include "Asteroid.h"
#include "AsteroidGameModeBase.h"
#include "UnlimitedGameMode.h"
#include "CustomPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ASpaceshipPawn::ASpaceshipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Movement Setup.
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
	MovementComponent->Acceleration = 1000.0f;
	MovementComponent->Deceleration = 650.0f;

	//Mesh Setup.
	spaceshipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	spaceshipMesh->SetupAttachment(RootComponent);
	spaceshipMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	//Spring Arm Setup.
	spaceshipArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	spaceshipArm->SetupAttachment(spaceshipMesh);
	spaceshipArm->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	spaceshipArm->SetRelativeRotation(FRotator(-25.0f, 0.0f, 0.0f));
	spaceshipArm->TargetArmLength = 600.0f;
	spaceshipArm->bEnableCameraLag = true;
	spaceshipArm->bEnableCameraRotationLag = true;
	spaceshipArm->CameraLagSpeed = 5.0f;
	spaceshipArm->CameraRotationLagSpeed = 5.0f;

	//Camera Setup.
	spaceshipCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	spaceshipCam->SetupAttachment(spaceshipArm);
	spaceshipCam->SetRelativeRotation(FRotator(12.0f, 0.0f, 0.0f));

	//Projectile Setup.
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(spaceshipMesh);
	ProjectileSpawnPoint->SetRelativeLocation(FVector(680.0f, 0.0f, 20.0f));
}

// Called when the game starts or when spawned
void ASpaceshipPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//Reference to gamemode classes and playercontroller class.
	GameModeRef = Cast<AAsteroidGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())); 
	PlayerRef = Cast<ACustomPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UnlimGameModeRef = Cast<AUnlimitedGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	//Creates a dyamic delegate for spaceship collision
	OnActorHit.AddDynamic(this, &ASpaceshipPawn::OnSpaceshipCollision);

	//Creates Player Controller.
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) //if not nullptr.
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()); //Sets up Enhanced Input System.
		
		//Adds spaceship mapping context and adds it to subsystem.
		Subsystem->AddMappingContext(SpaceshipMappingContext, 0);
	}
}

// Called every frame
void ASpaceshipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpaceshipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Casts EnhancedInputComponent to PlayerInputComponent.
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	/*
	* Binds all the Input Action Values, using their respective handler function
	* to allow for different controls
	*/

	//Movement Binding
	EIC->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ASpaceshipPawn::MoveForwardHandler);
	EIC->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &ASpaceshipPawn::LookUpHandler);
	EIC->BindAction(RollAction, ETriggerEvent::Triggered, this, &ASpaceshipPawn::RollHandler);

	//Shooting Binding
	EIC->BindAction(ReloadAction, ETriggerEvent::Completed, this, &ASpaceshipPawn::ReloadHandler);
	EIC->BindAction(FireAction, ETriggerEvent::Completed, this, &ASpaceshipPawn::FireHandler);

	//Switch Pawn Binding
	EIC->BindAction(SwitchAction, ETriggerEvent::Triggered, this, &ASpaceshipPawn::SwitchHandler);
}

void ASpaceshipPawn::MoveForwardHandler(const FInputActionValue& Value)
{
	if (GameModeRef != nullptr) //If we are using the GameModeRef class.
	{
		GameModeRef->GetFuel(FuelLeft); //Get current fuel.
		if (FuelLeft > 0) //If we have fuel.
		{
			MovementComponent->MaxSpeed = MoveSpeed; //Set MoveSpeed.
			AddMovementInput(GetActorForwardVector() * Value.Get<float>()); //Move Ship.
			GameModeRef->FuelDrain(); //Drain Spaceships Fuel.
		}
		else
		{
			GameModeRef->GameOver(true); //If no fuel Left lose game.
		}
	}
	else //If using UnlimitedGamemode class.
	{
		MovementComponent->MaxSpeed = MoveSpeed; //set Move Speed.
		AddMovementInput(GetActorForwardVector() * Value.Get<float>()); //Move Ship.
	}
}

void ASpaceshipPawn::LookUpHandler(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value.Get<float>() / RotationOffset); //Rotates Ship up and down.
}

void ASpaceshipPawn::RollHandler(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>() / RotationOffset); //Rotates ship left and right.
}

void ASpaceshipPawn::SwitchHandler(const FInputActionValue& Value)
{
	PlayerRef->SwitchPawn(); //Calls Switch Pawn method.
}

void ASpaceshipPawn::FireHandler(const FInputActionValue& Value)
{
	if (GameModeRef != nullptr) //If using gamemode ref class. 
	{
		GameModeRef->GetBullets(BulletCount); //Return amount of bullets.
	}
	if (BulletClass &&  BulletCount > 0) //checks projectile has been set in the editor and if there is bullets left.
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		ABullet* TempBullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation); //Spawns a bullet in the game.
		TempBullet->SetOwner(this);	//Makes that bullets owner the SpaceshipPawn.	
		if (GameModeRef != nullptr) //If using gamemode ref class. 
		{
			GameModeRef->FireBullet(); //Fire Bullet, decrement.
		}

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), shootSound, GetActorLocation(), 1.0f, 1.0f, 0.0f); //Plays a shooting sound when player fires bullet.
	}
}

void ASpaceshipPawn::ReloadHandler(const FInputActionValue& Value)
{
	if (GameModeRef != nullptr) //if using gamemoderef class.
	{	
		GameModeRef->ReloadBullets(); //Reload ships ammo.
	}
}

void ASpaceshipPawn::OnSpaceshipCollision(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetClass()->IsChildOf(AAsteroid::StaticClass())) //if the actor we collided with is an asteroid.
	{
		Destroy(); //Destroy the spaceship.
		if (GameModeRef != nullptr) //GamemodeRef class.
		{	
			GameModeRef->GameOver(true);
		}
		if (UnlimGameModeRef != nullptr) //UnlimGamemode class.
		{
			UnlimGameModeRef->GameEnd(false);
		}
	}
}

