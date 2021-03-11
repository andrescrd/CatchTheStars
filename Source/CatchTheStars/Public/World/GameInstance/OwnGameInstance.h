// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Support/Structures/LevelStruct.h"

#include "OwnGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API UOwnGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;

	// Managers
	UPROPERTY(Transient)
	class ULevelManager* LevelManagerInstance;
	UPROPERTY(Transient)
	class UDataManager* DataManagerInstance;
	UPROPERTY(Transient)
	class USoundManager* SoundManagerInstance;

	UPROPERTY(EditDefaultsOnly)
	class ULevelDataAsset* LevelDataAsset;

public:
	UFUNCTION(BlueprintCallable)
	class ULevelManager* GetLevelManager() const;
	UFUNCTION(BlueprintCallable)	
	class USoundManager* GetSoundManager() const;

	UFUNCTION(BlueprintCallable)
	TArray<FLevelStruct> GetAllLevels() const;

	UFUNCTION(BlueprintCallable)
	void Restart(UObject* Context) const;
	UFUNCTION(BlueprintCallable)
	void LoadMainMenu(UObject* Context) const;
	UFUNCTION(BlueprintCallable)
	void LoadMap(UObject* Context, FName MapName) const;
	UFUNCTION(BlueprintCallable)
	void LoadNextGameplayLevel(UObject* Context) const;

	virtual void Shutdown() override;
};
