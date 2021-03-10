// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Support/Structures/LevelStruct.h"

#include "OwnSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API UOwnSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FLevelStruct> Levels;
	UPROPERTY(VisibleAnywhere)
	uint32 UserIndex;
};
