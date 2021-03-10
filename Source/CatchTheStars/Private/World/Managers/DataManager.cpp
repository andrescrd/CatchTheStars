// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Managers/DataManager.h"

#include "Kismet/GameplayStatics.h"
#include "Support/Helpers/OwnSaveGame.h"

const FString SlotName = "CStar";

class UOwnSaveGame* UDataManager::GetSaveGameInstance()
{
	return IsValid(SaveGameInstance)
		       ? SaveGameInstance
		       : SaveGameInstance = Cast<UOwnSaveGame>(
			       UGameplayStatics::CreateSaveGameObject(UOwnSaveGame::StaticClass()));
}

void UDataManager::SaveLevels(const TArray<FLevelStruct> LevelStructs)
{
	GetSaveGameInstance()->Levels = LevelStructs;
	UGameplayStatics::SaveGameToSlot(GetSaveGameInstance(), SlotName, GetSaveGameInstance()->UserIndex);
}

TArray<FLevelStruct> UDataManager::GetLevels()
{
	if (UOwnSaveGame* LoadedGame = Cast<UOwnSaveGame>(
		UGameplayStatics::LoadGameFromSlot(SlotName, GetSaveGameInstance()->UserIndex)))
		return LoadedGame->Levels;

	return TArray<FLevelStruct>();
}

void UDataManager::ClearData() { UGameplayStatics::DeleteGameInSlot(SlotName, GetSaveGameInstance()->UserIndex); }
