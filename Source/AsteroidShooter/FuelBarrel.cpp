// Fill out your copyright notice in the Description page of Project Settings.


#include "FuelBarrel.h"
#include "AsteroidGameModeBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpinComponent.h"

// Sets default values
AFuelBarrel::AFuelBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Barrel mesh.
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	BarrelMesh->SetupAttachment(RootComponent);
	BarrelMesh->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));

	//Sphere component.
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	CollisionSphere->SetSphereRadius(75.0f);
	CollisionSphere->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	CollisionSphere->SetCollisionProfileName("Trigger");
	CollisionSphere->SetupAttachment(BarrelMesh);

	//Custom Spinning Component.
	SpinBarrel = CreateDefaultSubobject<USpinComponent>(TEXT("Spin Component"));
}

// Called when the game starts or when spawned
void AFuelBarrel::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<AAsteroidGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())); //Cast to our gamemode class. 
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AFuelBarrel::OnOverlapBegin); //Setup dynamic delegate for overlapping.
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AFuelBarrel::OnOverlapEnd); //Setup dynamic delegate for finishing overlap.
}

// Called every frame
void AFuelBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFuelBarrel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GameModeRef->AddFuel(); //Adds fuel to the ship when overlapping.
	Destroy(); //Destroys the barrel.
}

void AFuelBarrel::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

