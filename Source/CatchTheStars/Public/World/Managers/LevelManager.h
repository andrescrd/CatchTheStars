// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Assets/LevelDataAsset.h"
#include "Support/Structures/LevelStruct.h"
#include "UObject/NoExportTypes.h"
#include "LevelManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CATCHTHESTARS_API ULevelManager : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleInstanceOnly)
	FLevelStruct CurrentLevel;	
	UPROPERTY(VisibleInstanceOnly)
	FName LastLevelLoaded;	

	UPROPERTY(EditDefaultsOnly)
	FName Menu;
	UPROPERTY(EditDefaultsOnly)
	FName End;
	UPROPERTY(EditDefaultsOnly)
	TArray<FLevelStruct> Levels;
	
public:
	UFUNCTION(BlueprintCallable)    
	TArray<FLevelStruct> GetGameplayLevels() const;	
	UFUNCTION(BlueprintCallable)
    void LoadMenuLevel(class UWorld* Context);
	UFUNCTION(BlueprintCallable)
    void LoadEndLevel(class UWorld* Context);
	UFUNCTION(BlueprintCallable)
    void LoadGameplayLevel(class UWorld* World, FName MapName);
	UFUNCTION(BlueprintCallable)    
	void LoadNextGameplayLevel(UWorld* World);
	UFUNCTION(BlueprintCallable)
	static void Restart(class UWorld* Context);

	void Init(const TArray<FLevelStruct> OwnLevels, const FName OwnMainMenu,const FName OwnEnd);
};
