// Fill out your copyright notice in the Description page of Project Settings.


#include "World/GameInstance/OwnGameInstance.h"

#include "World/Managers/DataManager.h"
#include "World/Managers/LevelManager.h"

void UOwnGameInstance::Init()
{
	if (DataManagerInstance == nullptr)
		DataManagerInstance = NewObject<UDataManager>(this,TEXT("DataManagerInstance"));

	if (LevelManagerInstance == nullptr)
		LevelManagerInstance = NewObject<ULevelManager>(this, TEXT("LevelManagerInstance"));

	if (LevelDataAsset)
	{
		const auto Levels = LevelDataAsset->GetLevels();
		const auto Main = LevelDataAsset->MainMenu;
		const auto End = LevelDataAsset->End;

		LevelManagerInstance->Init(Levels, Main, End);
	}
}

ULevelManager* UOwnGameInstance::GetLevelManager() const { return LevelManagerInstance; }

TArray<FLevelStruct> UOwnGameInstance::GetAllLevels() const { return GetLevelManager()->GetGameplayLevels(); }

void UOwnGameInstance::Restart(UObject* Context) const
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	GetLevelManager()->Restart(World);
}

void UOwnGameInstance::LoadMainMenu(UObject* Context) const
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	GetLevelManager()->LoadMenuLevel(World);
}

void UOwnGameInstance::LoadMap(UObject* Context, const FName MapName) const
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	GetLevelManager()->LoadGameplayLevel(World, MapName);
}

void UOwnGameInstance::LoadNextGameplayLevel(UObject* Context) const
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	GetLevelManager()->LoadNextGameplayLevel(World);
}
