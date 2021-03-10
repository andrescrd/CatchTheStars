// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Support/Structures/LevelStruct.h"
#include "UObject/NoExportTypes.h"
#include "DataManager.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API UDataManager : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleInstanceOnly)
	class UOwnSaveGame* SaveGameInstance;
	class UOwnSaveGame* GetSaveGameInstance();
	
public:
	void SaveLevels(const TArray<FLevelStruct> LevelStructs);
	TArray<FLevelStruct>  GetLevels();
	void ClearData();	
};
