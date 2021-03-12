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

FName ULevelManager::GetLastLevelLoaded() const { return  LastLevelLoaded; }

void ULevelManager::UpdateTime(const FName LevelName, const int Time)
{
	for (int i = 0; i < Levels.Num(); ++i)
	{
		FLevelStruct& Level = Levels[i];		
		if(Level.LevelName.IsEqual(LevelName) && (Level.MaxTime == 0 || Level.MaxTime > Time))
		{
			Level.MaxTime = Time;
			break;
		}
	}	
}

TArray<FLevelStruct> ULevelManager::GetGameplayLevels() const { return Levels; }

void ULevelManager::LoadMainMenu(UWorld* World)
{
	LastLevelLoaded = Menu;
	UGameplayStatics::OpenLevel(World, Menu);
}

void ULevelManager::LoadEnd(UWorld* World)
{
	LastLevelLoaded = End;
	UGameplayStatics::OpenLevel(World, End);
}

void ULevelManager::LoadGameplayLevel(UWorld* World, const FName LevelName)
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

	UE_LOG(LogTemp, Warning, TEXT("Open level: %s"),*LevelName.ToString());
	const FLatentActionInfo Info;
	UGameplayStatics::LoadStreamLevel(World, LevelName, true, true, Info);

	LastLevelLoaded = LevelName;
}

void ULevelManager::LoadNextGameplayLevel(UWorld* World)
{
	FName NextGameplayLevel = NAME_None;

	for (int32 Index = 0; Index < Levels.Num(); Index++)
	{
		if (Levels[Index].LevelName.IsEqual(LastLevelLoaded))
		{
			NextGameplayLevel = (Index + 1 == Levels.Num()) ?  End : Levels[Index + 1].LevelName;
			break;
		}
	}

	if (NextGameplayLevel == Menu)
		LoadMainMenu(World);

	else if (NextGameplayLevel == End)
		LoadEnd(World);
	else
	{
		const int32 Index = Levels.FindLastByPredicate([NextGameplayLevel](const FLevelStruct LevelSetup)
        {
            return LevelSetup.LevelName == NextGameplayLevel;
        });

		if (Index != INDEX_NONE)
		{
			Levels[Index].IsAvailable = true;
			LoadGameplayLevel(World, NextGameplayLevel);
		}
	}
}

void ULevelManager::Restart(UWorld* World)
{
	const FString LevelName = UGameplayStatics::GetCurrentLevelName(World);
	LastLevelLoaded = NAME_None;
	UGameplayStatics::OpenLevel(World, *LevelName);
}
