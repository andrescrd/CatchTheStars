// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Managers/LevelManager.h"

#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"

void ULevelManager::Init(const TArray<FLevelStruct> OwnLevels, const FName OwnMainMenu,const FName OwnEnd)
{
	Levels = OwnLevels;
	Menu =OwnMainMenu;
	End = OwnEnd;
}

TArray<FLevelStruct> ULevelManager::GetGameplayLevels() const { return Levels; }

void ULevelManager::LoadMenuLevel(UWorld* Context)
{
	LastLevelLoaded = Menu;
	UGameplayStatics::OpenLevel(Context, Menu);
}

void ULevelManager::LoadEndLevel(UWorld* Context)
{
	LastLevelLoaded = End;
	UGameplayStatics::OpenLevel(Context, End);
}

void ULevelManager::LoadGameplayLevel(UWorld* World, const FName MapName)
{
	if (LastLevelLoaded.GetStringLength() > 0 && LastLevelLoaded != NAME_None)
	{
		ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(World, LastLevelLoaded);

		if(LevelStreaming != nullptr)
		{
			LevelStreaming->SetShouldBeVisible(false);
			LevelStreaming->SetIsRequestingUnloadAndRemoval(true);
		}
	}

	const FLatentActionInfo Info;
	UGameplayStatics::LoadStreamLevel(World, MapName, true, true, Info);

	LastLevelLoaded = MapName;
}

void ULevelManager::LoadNextGameplayLevel(UWorld* World)
{
	FName NextGameplayLevel = NAME_None;

	for (int32 Index = 0; Index < Levels.Num(); Index++)
	{
		if (Levels[Index].MapName.IsEqual(LastLevelLoaded))
		{
			NextGameplayLevel = (Index + 1 == Levels.Num()) ?  End : Levels[Index + 1].MapName;
			break;
		}
	}

	if (NextGameplayLevel == Menu)
		LoadMenuLevel(World);

	else if (NextGameplayLevel == End)
		LoadEndLevel(World);
	else
	{
		const int32 Index = Levels.FindLastByPredicate([NextGameplayLevel](const FLevelStruct LevelSetup)
        {
            return LevelSetup.MapName == NextGameplayLevel;
        });

		if (Index != INDEX_NONE)
		{
			Levels[Index].IsAvailable = true;
			LoadGameplayLevel(World, NextGameplayLevel);
		}
	}
}

void ULevelManager::Restart(UWorld* Context)
{
	const FString LevelName = UGameplayStatics::GetCurrentLevelName(Context);
	LastLevelLoaded = NAME_None;
	UGameplayStatics::OpenLevel(Context, *LevelName);
}
