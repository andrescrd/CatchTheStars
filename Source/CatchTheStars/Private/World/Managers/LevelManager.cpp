// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Managers/LevelManager.h"

#include "Assets/LevelDataAsset.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"


void ULevelManager::SetGameplayLevels(TArray<FLevelStruct> LevelStructs) { Levels = LevelStructs; }

TArray<FLevelStruct> ULevelManager::GetGameplayLevels() const { return Levels; }

void ULevelManager::LoadMenuLevel(UWorld* Context)
{
	LastLevelLoaded = Menu.MapName;
	UGameplayStatics::OpenLevel(Context, Menu.MapName);
}

void ULevelManager::LoadEndLevel(UWorld* Context)
{
	LastLevelLoaded = End.MapName;
	UGameplayStatics::OpenLevel(Context, End.MapName);
}

void ULevelManager::LoadGameplayLevel(UWorld* World, const FName MapName)
{
	if (LastLevelLoaded.GetStringLength() > 0 && LastLevelLoaded != NAME_None)
	{
		ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(World, LastLevelLoaded);
		LevelStreaming->SetShouldBeVisible(false);
		LevelStreaming->SetIsRequestingUnloadAndRemoval(true);
	}

	const FLatentActionInfo Info;
	UGameplayStatics::LoadStreamLevel(World, MapName, true, true, Info);

	LastLevelLoaded = MapName;
}

void ULevelManager::Restart(UWorld* Context)
{
	const FString LevelName = UGameplayStatics::GetCurrentLevelName(Context);
	UGameplayStatics::OpenLevel(Context, *LevelName);
}
