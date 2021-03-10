// Fill out your copyright notice in the Description page of Project Settings.


#include "Assets/LevelDataAsset.h"

TArray<FLevelStruct> ULevelDataAsset::GetLevels() const { return LevelSetup; }

FLevelStruct ULevelDataAsset::GetLevelByName(FName LevelName)
{
	const FLevelStruct *LevelByName = LevelSetup.FindByPredicate([LevelName](const FLevelStruct Level)
	{
		return (Level.MapName == LevelName);
		// 	return ;
		//
		// return Level;
	});

	return *LevelByName;
}

FLevelStruct ULevelDataAsset::GetLastAvailableLevel() const
{
	auto FilteredLevel = LevelSetup.FilterByPredicate([](const FLevelStruct Level)
	{
		return  (Level.IsAvailable);
			// return Level;
	});

	return FilteredLevel.Num() > 0 ? FilteredLevel[FilteredLevel.Num() - 1] : FLevelStruct();
}
