// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

	UPROPERTY(EditDefaultsOnly)
	class ULevelDataAsset* LevelDataAsset;

public:
	ULevelManager* GetLevelManager() const;
	
};
