// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndLevelGameMode.generated.h"

class AUnlimitedGameMode;

UCLASS()
class ASTEROIDSHOOTER_API AEndLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	APawn* myPawn;
};
