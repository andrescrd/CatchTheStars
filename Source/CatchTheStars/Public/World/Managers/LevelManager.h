// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Support/Structures/LevelStruct.h"
#include "UObject/NoExportTypes.h"
#include "LevelManager.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API ULevelManager : public UObject
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleInstanceOnly)
	FLevelStruct CurrentLevel;	
	UPROPERTY(VisibleInstanceOnly)
	FName LastLevelLoaded;	

	UPROPERTY(EditDefaultsOnly)
	FLevelStruct Menu;
	UPROPERTY(EditDefaultsOnly)
	FLevelStruct End;
	UPROPERTY(EditDefaultsOnly)
	TArray<FLevelStruct> Levels;
	
public:
	void SetGameplayLevels(TArray<FLevelStruct> LevelStructs);
	TArray<FLevelStruct> GetGameplayLevels() const;
	
	UFUNCTION(BlueprintCallable)
    void LoadMenuLevel(class UWorld* Context);
	UFUNCTION(BlueprintCallable)
    void LoadEndLevel(class UWorld* Context);
	UFUNCTION(BlueprintCallable)
    void LoadGameplayLevel(class UWorld* World, FName MapName);
	UFUNCTION(BlueprintCallable)
    void Restart(class UWorld* Context);
};
