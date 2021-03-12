// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Support/Structures/LevelStruct.h"
#include "UObject/NoExportTypes.h"
#include "LevelManager.generated.h"

UCLASS()
class CATCHTHESTARS_API ULevelManager : public UObject
{
	GENERATED_BODY()

protected:	
	FName Menu;
	FName End;
	TArray<FLevelStruct> Levels;
	FLevelStruct CurrentLevel;	
	FName LastLevelLoaded;	
	
public:

	UFUNCTION(BlueprintCallable)    
	TArray<FLevelStruct> GetGameplayLevels() const;	
	UFUNCTION(BlueprintCallable)
    void LoadMainMenu(class UWorld* World);
	UFUNCTION(BlueprintCallable)
    void LoadEnd(class UWorld* World);
	UFUNCTION(BlueprintCallable)
    void LoadGameplayLevel(class UWorld* World, FName LevelName);
	UFUNCTION(BlueprintCallable)    
	void LoadNextGameplayLevel(UWorld* World);
	UFUNCTION(BlueprintCallable)    
	void UpdateTime(const FName LevelName, const int Time);

	UFUNCTION(BlueprintCallable)
	void Restart(class UWorld* World);

	void Init(const TArray<FLevelStruct> OwnLevels, const FName OwnMainMenu,const FName OwnEnd);	
};