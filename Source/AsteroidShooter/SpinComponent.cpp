// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinComponent.h"

// Sets default values for this component's properties
USpinComponent::USpinComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpinComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void USpinComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	AActor* actor = GetOwner(); //Gets the owner of the spin component.
	if (!actor) { return; } //Stops editor Crash if there is no owner.

	FRotator Rotation; 

	//Rotate the actor in roll and yaw with delta time.
	Rotation.Roll = SpinSpeed * DeltaTime;
	Rotation.Yaw = SpinSpeed * DeltaTime;

	//adds a local rotation to the actor using the above calculations.
	actor->AddActorLocalRotation(Rotation);
}

