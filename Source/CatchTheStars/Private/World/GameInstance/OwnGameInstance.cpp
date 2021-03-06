// Fill out your copyright notice in the Description page of Project Settings.


#include "World/GameInstance/OwnGameInstance.h"


#include "Assets/LevelDataAsset.h"
#include "World/Managers/DataManager.h"
#include "World/Managers/LevelManager.h"
#include "World/Managers/SoundManager.h"

void UOwnGameInstance::Init()
{
	if (DataManagerInstance == nullptr)
		DataManagerInstance = NewObject<UDataManager>(this,TEXT("DataManagerInstance"));

	if (LevelManagerInstance == nullptr)
		LevelManagerInstance = NewObject<ULevelManager>(this, TEXT("LevelManagerInstance"));

	if (SoundManagerInstance == nullptr)
		SoundManagerInstance = NewObject<USoundManager>(this, TEXT("SoundManagerInstance"));

	SetupLevels();
}

void UOwnGameInstance::SetupLevels() const
{
	if (!LevelDataAsset)
		return;
	
	const auto Levels = LevelDataAsset->GetLevels();
	const auto Main = LevelDataAsset->MainMenu;
	const auto End = LevelDataAsset->End;

	const auto StoredLevels = DataManagerInstance->GetLevels();

	if (StoredLevels.Num() == 0)
		DataManagerInstance->SaveLevels(Levels);

	LevelManagerInstance->Init(StoredLevels.Num() == 0 ? Levels : StoredLevels, Main, End);
}

ULevelManager* UOwnGameInstance::GetLevelManager() const { return LevelManagerInstance; }

USoundManager* UOwnGameInstance::GetSoundManager() const { return SoundManagerInstance; }

TArray<FLevelStruct> UOwnGameInstance::GetAllLevels() const { return GetLevelManager()->GetGameplayLevels(); }

void UOwnGameInstance::Restart(UObject* Context) const
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	GetLevelManager()->Restart(World);
}

void UOwnGameInstance::LoadMainMenu(UObject* Context) const
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	GetLevelManager()->LoadMainMenu(World);
}

void UOwnGameInstance::LoadCurrentGameplayLevel(UObject* Context) const
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	GetLevelManager()->LoadGameplayLevel(World, CurrentMap);
}

void UOwnGameInstance::LoadNextGameplayLevel(UObject* Context)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	GetLevelManager()->LoadNextGameplayLevel(World);
	CurrentMap = GetLevelManager()->GetLastLevelLoaded();
}

void UOwnGameInstance::SetLevelNameToLoad(const FName MapName) { CurrentMap = MapName; }

void UOwnGameInstance::SetTimeOnCurrentLevel(const int Time) const { GetLevelManager()->UpdateTime(CurrentMap, Time); }

void UOwnGameInstance::Shutdown()
{
	Super::Shutdown();
	DataManagerInstance->SaveLevels(GetAllLevels());
}
