// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Asteroid.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Bullet mesh.
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetRelativeScale3D(FVector(5.0f, 5.0f, 5.0f));

	RootComponent = BulletMesh;
	BulletMesh->SetSimulatePhysics(true); //Sets up physics for the bullet movement.
	
	//Projectile Component.
	BulletProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Bullet Projectile"));

	//Porjectile Component Params.
	BulletProjectile->MaxSpeed = MovementSpeed;
	BulletProjectile->InitialSpeed = MovementSpeed;
	InitialLifeSpan = 3.0f;

	//Creates Rigidbody for the bullet used in collision.
	BulletMesh->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ABullet::OnHit); //Creates a dynamic delegate for when hitting an actor.
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetClass()->IsChildOf(AAsteroid::StaticClass())) //if a child class of asteroid.
	{
		AActor* ProjectileOwner = GetOwner(); //Gets the owner of the projectile (Spaceship).

		if (ProjectileOwner == nullptr) { return; } //if no owner then we dont do anything.

		UGameplayStatics::ApplyDamage(OtherActor, BulletDamage, ProjectileOwner->GetInstigatorController(), this, UDamageType::StaticClass()); //Apply the damage to the actor using unreal damage system.

		Destroy(); //Destroy the bullet.
	}
}

