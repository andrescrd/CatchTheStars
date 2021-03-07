// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API AGameplayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameplayGameMode();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnGameFinish();

public:
	void Finish();
};