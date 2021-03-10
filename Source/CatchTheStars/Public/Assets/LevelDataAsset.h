// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Support/Structures/LevelStruct.h"

#include "LevelDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API ULevelDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)	
	TArray<FLevelStruct> LevelSetup;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)	
	FName MainMenu;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)	
	FName End;
	
	UFUNCTION(BlueprintCallable)
	TArray<FLevelStruct> GetLevels() const;
	UFUNCTION(BlueprintCallable)
	FLevelStruct GetLevelByName(FName LevelName);
	UFUNCTION(BlueprintCallable)
	FLevelStruct GetLastAvailableLevel() const;
};
